#include "player.h"

player::player(string projectFilePath)
{
    this->projectFilePath = projectFilePath;
}

void player::loadNode(int newNodeId)
{
    int prevNodeId = 0;
    
    if(currNode != NULL) prevNodeId = currNode->getId();
    
    // prepare the new node for loading if not loaded
    if(nodeStatus.count(newNodeId) == 0)
    {
        nodeStatus.insert(pair<int, string>(newNodeId, "loading"));
        loadingQueue.push(newNodeId);
    }
    
    // prepare the new node neighbors to load
    map<int,node>::iterator iter = nodes.find(newNodeId); //if(iter != nodes.end())
    
    map<string, int> nodeNeighbors = iter->second.getAdjacentNodes();
    map<string, int>::iterator i;
        
    for(i = nodeNeighbors.begin(); i != nodeNeighbors.end(); i++)
    {
        int neighborNodeId = i->second; 
        if(nodeStatus.count(neighborNodeId) == 0)
        {
            nodeStatus.insert(pair<int, string>(neighborNodeId, "loading"));
            loadingQueue.push(neighborNodeId);
        }
    }

    // get the new node layers
    set<int> layersToKeep = iter->second.getLayersId();
    set<int> nodesToKeep;    
    nodesToKeep.insert(newNodeId);
    
    // unload the neighbors of the previous node
    iter = nodes.find(prevNodeId); //if(iter != nodes.end())
    
    set<int> layersToDelete, nodesToDelete;
    
    iter->second.unloadAdjacentNodes(layersToKeep, nodesToKeep, layersToDelete, nodesToDelete);
    
    set<int>::iterator delIt;
    for(delIt = layersToDelete.begin(); delIt != layersToDelete.end(); delIt++)
    {
        layersActive.erase((*delIt));
    }
    for(delIt = nodesToDelete.begin(); delIt != nodesToDelete.end(); delIt++)
    {
        nodeStatus.erase((*delIt));
    }
    cout << "node status count: " << nodeStatus.size() << endl;
    cout << "layersActive count: " << layersActive.size() << endl;
    cout << "loadingQueue count: " << loadingQueue.size() << endl;
    
}

void player::mocksetup()
{
    
}

//--------------------------------------------------------------
void player::update()
{
    if(currNode != NULL)
    {
        if(!currNode->isPlaying()) currNode->play();
        if(currNode->isLoaded()) currNode->update();
    }    

    //kinect.update();
}

//--------------------------------------------------------------
void player::draw()
{
    ofBackground(0,0,0);
    if(currNode != NULL && currNode->isLoaded())    
        currNode->draw();
    //kinect.draw();
}

void player::setup()
{
    //kinect.setup();
    
    // load project file
    bool success = jsonProject.openLocal(this->projectFilePath);
	if (success)
	{
        // read and load layers and items from project
        for(int i = 0u; i != jsonProject["layers"].size(); ++i)
        {
            // read item properties
            string localURL = jsonProject["layers"][i]["attr"]["localurl"].asString();
            string originalURL = jsonProject["layers"][i]["attr"]["url"].asString();
            string mediaType = jsonProject["layers"][i]["type"].asString();

            // read layer properties
            layerPtr l = this->createLayerForItem(mediaType, localURL);
            l->setX(0);
            l->setY(0);
            l->setHeight(ofGetHeight());
            l->setWidth(ofGetWidth());
            l->setVolume(jsonProject["layers"][i]["volume"].asDouble());
            l->setInTime(jsonProject["layers"][i]["in"].asDouble());
            l->setOutTime(jsonProject["layers"][i]["out"].asDouble());
            l->setOpacity(jsonProject["layers"][i]["opacity"].asDouble());
            l->setAspectRatio(jsonProject["layers"][i]["aspectRatio"].asDouble());
            l->setId(jsonProject["layers"][i]["id"].asInt());
            
            layers.insert(pair<int, layerPtr>(l->getId(), l));
        }
        
        for(int i = 0u; i != jsonProject["nodes"].size(); ++i)
        {
            int nodeId = jsonProject["nodes"][i]["id"].asInt();
            cout << "node id " << nodeId << endl;
            node n;
            n.setId(nodeId);
            
            int adjacentNodeLeftId = jsonProject["nodes"][i]["link_left_id"].asInt();
            int adjacentNodeRighttId = jsonProject["nodes"][i]["link_right_id"].asInt();
            int adjacentNodeUpId = jsonProject["nodes"][i]["link_up_id"].asInt();
            cout << "adjacentNodeRighttId " << adjacentNodeRighttId << endl;
            int adjacentNodeDownId = jsonProject["nodes"][i]["link_down_id"].asInt();
            
            if(adjacentNodeLeftId != 0)     n.addAdjacentNode("LEFT", adjacentNodeLeftId);
            if(adjacentNodeRighttId != 0)   n.addAdjacentNode("RIGHT", adjacentNodeRighttId);
            if(adjacentNodeUpId != 0)       n.addAdjacentNode("UP", adjacentNodeUpId);
            if(adjacentNodeDownId != 0)     n.addAdjacentNode("DOWN", adjacentNodeDownId);
            
            for(int j = 0u; j != jsonProject["nodes"][i]["layers"].size(); ++j)
            {
                int nodeLayerId = jsonProject["nodes"][i]["layers"][j].asInt();
                map<int,layerPtr>::iterator layerIt = layers.find(nodeLayerId);
                
                if (layerIt != layers.end())
                {
                    layerPtr li = layerIt->second;
                    cout << li->getId();
                    n.addLayer(li);
                }
                else
                {
                    cout << "something went wrong";
                }
            
            }
            cout << "Inserting node " << nodeId << endl;
            nodes.insert(pair<int, node>(nodeId, n));
        }
	}
    
    map<int,node>::iterator iter = nodes.find(11590);
    /*currNode = &iter->second;
    currNode->load();
    currNode->play();
     */
    loadNode(11590);
}

layerPtr player::createLayerForItem(string itemType, string localURI)
{
    layerPtr newLayer;
    transform(itemType.begin(), itemType.end(),itemType.begin(), ::toupper);
    
    if(itemType == "VIDEO")
    {
        videoLayer* v = new videoLayer;
        v->setX(0);
        v->setY(0);
        v->setWidth(ofGetScreenWidth());
        v->setHeight(ofGetScreenHeight());
        
        newLayer = layerPtr(v);
    }
    else if(itemType == "AUDIO")
    {
        newLayer = layerPtr(new audioLayer);
    }
    else if(itemType == "IMAGE")
    {
        imageLayer* v = new imageLayer;
        v->setX(0);
        v->setY(0);
        v->setWidth(ofGetScreenWidth());
        v->setHeight(ofGetScreenHeight());

        newLayer = layerPtr(v);
    }
    else
    {
        cout << "something went wrong" << endl;
    }
    
    //newLayer->load(&item);
    newLayer->setup(localURI);
    newLayer->setWidth(ofGetScreenWidth());
    newLayer->setWidth(ofGetScreenHeight());
    newLayer->setX(0);
    newLayer->setY(0);
    
    return newLayer;
}

void player::keyPressed  (int key)
{
    int id;
    
    switch(key)
    {
        case OF_KEY_LEFT:
            id = currNode->getAdjacentNode("LEFT");
            break;
        case OF_KEY_RIGHT:
            id = currNode->getAdjacentNode("RIGHT");
            break;
        case OF_KEY_UP:
            id = currNode->getAdjacentNode("UP");
            break;
        case OF_KEY_DOWN:
            id = currNode->getAdjacentNode("DOWN");
            break;    
    }
    
    cout << "Switching to node " << id;
    map<int,node>::iterator iter = nodes.find(id);
    
    if(iter != nodes.end())
    {   
        currNode->stop();
        currNode = &(iter->second);
        cout << "Switching to node 2 " << currNode->getId();
        currNode->load();
        currNode->play();
    }
}

//--------------------------------------------------------------
void player::keyReleased(int key){
    
}
