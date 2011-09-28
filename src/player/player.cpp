#include "player.h"

player::player(string projectFilePath)
{
    this->projectFilePath = projectFilePath;
}

void player::loadNode(int newNodeId)
{
    cout << "loadNode " << currRoute << " " << newNodeId << endl;
    int prevNodeId = 0;
    
    // get the new node and the list of layers
    map<int,node>::iterator newNodeIt = nodes.find(newNodeId); 
    newNodeIt->second.load();
    
    // if there was a node previously loaded...
    if(currNode != NULL) 
    {
        // get the layers for the new node
        set<int> newNodeLayers = newNodeIt->second.getLayersId();

        // unload all the layers from the previous node except the ones that
        // occur in the new node
        currNode->unload(newNodeLayers);
    }
    
    currNode = &newNodeIt->second;
    
    routes[currRoute] = currNode;
}

void player::mocksetup()
{
    
}

//--------------------------------------------------------------
void player::update()
{
    if(currNode != NULL)
    {
        if(currNode->isLoaded()) 
        {    
            currNode->update();
        }
        if(!currNode->isPlaying()) 
        {    
            currNode->play();
        }
    }    
#ifdef USE_KINECT    
    kinect.update();
#endif
}

//--------------------------------------------------------------
void player::draw()
{
    ofBackground(0,0,0);
    if(currNode != NULL && currNode->isLoaded())    
        currNode->draw();
#ifdef USE_KINECT    
    kinect.draw();
#endif
    
}

void player::gestureListener(gesture & g)
{
    int routeNumber;
    if(g.gesture_name == "Click" || g.gesture_name == "Wave")
    {
        
        if(g.gesture_name == "Click" && currRoute == 1)
        {
            float xPos = g.gesture_position.x;
            cout << xPos << endl;
            if(xPos < -134) routeNumber = 2;
            else if((xPos > -134) && (xPos < 202)) routeNumber = 3;
            else routeNumber = 4;
        }
        else if(g.gesture_name == "Wave")
        {
            routeNumber = 1;
        }
        currRoute = routeNumber;
        int id = routes.find(routeNumber)->second->getId();
        loadNode(id);
    }
}

void player::setup()
{
#ifdef USE_KINECT    
    kinect.setup();
    ofAddListener(kinect.recordGestures.gestureRecognized, this, &player::gestureListener);
#endif
    
    this->currNode = NULL;
    
    
    // load project file
    bool success = jsonProject.openLocal(this->projectFilePath);
	int firstNodeToLoad;
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
            l->setId(jsonProject["layers"][i]["id"].asInt());
            cout << "media type " << mediaType << endl;
            cout << "id " << jsonProject["layers"][i]["id"].asInt() << endl;
            l->setX(jsonProject["layers"][i]["attr"]["x"].asInt());
            l->setY(jsonProject["layers"][i]["attr"]["y"].asInt());
            l->setHeight(jsonProject["layers"][i]["attr"]["h"].asInt());
            l->setWidth(jsonProject["layers"][i]["attr"]["w"].asInt());
            l->setVolume(jsonProject["layers"][i]["attr"]["volume"].asDouble());
            l->setInTime(jsonProject["layers"][i]["attr"]["in"].asDouble());
            l->setOutTime(jsonProject["layers"][i]["attr"]["out"].asDouble());
            //l->setOpacity(jsonProject["layers"][i]["attr"]["opacity"].asInt());
            l->setAspectRatio(jsonProject["layers"][i]["attr"]["aspectRatio"].asDouble());
            
            
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
        
        
        int firstNodeToLoad;
        for(int i = 0u; i != jsonProject["routes"].size(); ++i)
        {
            int routeId = jsonProject["routes"][i]["id"].asInt();
            int startNode = jsonProject["routes"][i]["start_id"].asInt();
            cout << routeId << endl;
            cout << startNode << endl;
            
            map<int,node>::iterator nodeIt = nodes.find(startNode);
            routes.insert(pair<int,node*>(routeId, &nodeIt->second));    
            
            if(routeId == 1)
            {
                firstNodeToLoad = startNode;
            }
        }

	}
    cout << firstNodeToLoad << endl;
    currRoute = 1;
    loadNode(10065);
}

layerPtr player::createLayerForItem(string itemType, string localURI)
{
    layerPtr newLayer;
    transform(itemType.begin(), itemType.end(),itemType.begin(), ::toupper);
    
    if(itemType == "VIDEO")
    {
        videoLayer* v = new videoLayer;
        
        newLayer = layerPtr(v);
    }
    else if(itemType == "AUDIO")
    {
        audioLayer* a = new audioLayer;
        newLayer = layerPtr(a);
    }
    else if(itemType == "IMAGE")
    {
        imageLayer* v = new imageLayer;

        newLayer = layerPtr(v);
    }
    else
    {
        cout << "something went wrong" << endl;
    }
    cout << "creating " << localURI << endl;
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
        case OF_KEY_PAGE_DOWN:    
        case OF_KEY_LEFT:
            id = currNode->getAdjacentNode("LEFT");
            break;
        case OF_KEY_PAGE_UP:    
        case OF_KEY_RIGHT:
            id = currNode->getAdjacentNode("RIGHT");
            break;
        case OF_KEY_UP:
            id = currNode->getAdjacentNode("UP");
            break;
        case OF_KEY_DOWN:
            id = currNode->getAdjacentNode("DOWN");
            break;
        case '1':
            id = routes.find(2)->second->getId();
            currRoute = 2;
            break;
        case '2':
            id = routes.find(3)->second->getId();
            currRoute = 3;
            break;   
        case '3':
            id = routes.find(4)->second->getId();
            currRoute = 4;
            break;
        case '4':
        case '.':
            id = routes.find(1)->second->getId();
            currRoute = 1;
            break;
    }
    
    map<int,node>::iterator iter = nodes.find(id);
    
    if(iter != nodes.end())
    {
        loadNode(id);
    }
#ifdef USE_KINECT        
    kinect.keyPressed(key);
#endif
}

//--------------------------------------------------------------
void player::keyReleased(int key){
    
}

