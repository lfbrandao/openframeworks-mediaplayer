#include "player.h"

player::player(string projectFilePath)
{
    this->projectFilePath = projectFilePath;
}

void player::mocksetup()
{
    /*string testUrl = "/Users/luisbrandao/Documents/metaLAB/code/revere-small/6996758.mp3";
    node n;
    n.setId(1500);
    
    layerPtr newLayer = layerPtr(new videoLayer);
    newLayer->setId(5);
    newLayer->setup(testUrl, 0, 100);

    layers.insert(pair<int, layerPtr>(newLayer->getId(), newLayer));
    
    n.addLayer(newLayer);
    //newLayer->play();
    nodes.insert(pair<int, node>(1500, n));
    
    map<int,node>::iterator iter = nodes.find(1500);
    currNode = &iter->second;
    currNode->play();*/
    layerPtr newLayer = layerPtr(new videoLayer);
    newLayer->setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", 200, 200, 0, 0, 0, 0);
    node n;
    n.setId(1500);
    n.addLayer(newLayer);
    
    currNode = &n;
}

//--------------------------------------------------------------
void player::update()
{
    currNode->update();
    //kinect.update();
}

//--------------------------------------------------------------
void player::draw()
{
    ofBackground(0,0,0);
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
            /*
            l->setX(jsonProject["layers"][i]["x"].asDouble());
            l->setY(jsonProject["layers"][i]["y"].asDouble());
            l->setHeight(jsonProject["layers"][i]["h"].asDouble());
            l->setWidth(jsonProject["layers"][i]["w"].asDouble());
             */
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
    currNode = &iter->second;
    currNode->play();
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
    newLayer->setup(localURI, ofGetScreenWidth(),ofGetScreenHeight(), 0, 0, 0,0);
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
        currNode->play();
    }
}

//--------------------------------------------------------------
void player::keyReleased(int key){
    
}
