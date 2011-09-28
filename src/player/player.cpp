#include "player.h"

player::player(string projectFilePath)
{
    this->projectFilePath = projectFilePath;
}

void player::loadNode(int newNodeId)
{
    stopKinect = true;
    
    visibleRegionOfInterest->setX(0); 
    visibleRegionOfInterest->setY(0); 
    visibleRegionOfInterest->setWidth(ofGetWidth());
    visibleRegionOfInterest->setHeight(ofGetHeight());

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
    
    if(kinect.tracking && !stopKinect)
    {
        int positionX = kinect.position.X;
        int positionZ = kinect.position.Z;
        
        list<kinectZone>::iterator itImg;
        
        for(itImg = kinectZones.begin(); itImg != kinectZones.end(); itImg++)
        {
            if( (itImg->getXLow() < positionX) && 
               (itImg->getXHigh() > positionX) &&
               (itImg->getZLow() < positionZ) && 
               (itImg->getZHigh() > positionZ) )
            {
                this->changeRegionOfInterest(itImg->getImageRegion());
                break;
            }    
        }
    }
    
    if(currRegionOfInterest != visibleRegionOfInterest)
    {
        float targetX = currRegionOfInterest->getX();
        float targetY = currRegionOfInterest->getY();
        float targetZoom = currRegionOfInterest->getZoomPercentage();
        
        float visibleX = visibleRegionOfInterest->getX();
        float visibleY = visibleRegionOfInterest->getY();
        float visibleZoom = visibleRegionOfInterest->getZoomPercentage();
        
        float diffX = abs(targetX - visibleX);
        float diffY = abs(targetY - visibleY);
        
        float zoomDif = abs(visibleZoom - targetZoom);
        /*
         cout 
         << " targetX " << targetX
         << "; targetY " << targetY
         << "; targetZoom " << targetZoom
         << "; visibleX " << visibleX
         << "; visibleY " << visibleY
         << "; visibleZoom " << visibleZoom
         << "; diffX " << diffX
         << "; zoomDif " << zoomDif
         << "; diffY" << diffY << endl;
         */
        if(diffY > 0 || diffX > 0)
        {
            if(diffX >= diffY)
            {
                cout << "moveStep " << moveStep << endl;
                if(diffX >= moveStep)
                {
                    if(visibleX > targetX) visibleX = visibleX - moveStep;
                    if(visibleX < targetX) visibleX = visibleX + moveStep;
                }
                else
                {
                    if(visibleX > targetX) visibleX = visibleX - diffX;
                    if(visibleX < targetX) visibleX = visibleX + diffX;
                }
                
                if(diffY > 0) visibleY = targetY * visibleX / targetX;
            }
            else
            {
                if(diffY >= moveStep)
                {
                    if(visibleY > targetY) visibleY = visibleY - moveStep;
                    if(visibleY < targetY) visibleY = visibleY + moveStep;
                }
                else
                {
                    if(visibleY > targetY) visibleY = visibleY - diffY;
                    if(visibleY < targetY) visibleY = visibleY + diffY;
                }
                
                if(diffX > 0) visibleX = targetX * visibleY / targetY;
            }
        }
        
        if(isnan(visibleX)) visibleX = 0;
        if(isnan(visibleY)) visibleY = 0;
        
        visibleRegionOfInterest->setY(visibleY);
        visibleRegionOfInterest->setX(visibleX);
        
        // zoom
        if(visibleZoom != targetZoom)
        {
            if(visibleZoom < targetZoom)
            {
                visibleZoom = visibleZoom + zoomStep;
                visibleRegionOfInterest->setZoomPercentage(visibleZoom);
            }
            else
            {
                visibleZoom = visibleZoom - zoomStep;
                visibleRegionOfInterest->setZoomPercentage(visibleZoom);
            }
            
            visibleRegionOfInterest->setWidth(ofGetWidth() * visibleZoom / 100);
            visibleRegionOfInterest->setHeight(ofGetHeight() * visibleZoom / 100);
        }
    }
    
    kinect.update();
}

void player::changeRegionOfInterest(imageRegion* newImageRegion)
{
    this->currRegionOfInterest = &(*newImageRegion);
    
    float targetX = currRegionOfInterest->getX();
    float targetY = currRegionOfInterest->getY();
    float targetZoom = currRegionOfInterest->getZoomPercentage();
    
    float visibleX = visibleRegionOfInterest->getX();
    float visibleY = visibleRegionOfInterest->getY();
    float visibleZoom = visibleRegionOfInterest->getZoomPercentage();
    
    float diffX = abs(targetX - visibleX);
    float diffY = abs(targetY - visibleY);
    
    float zoomDif = abs(visibleZoom - targetZoom);
    
    
    cout 
    << " targetX " << targetX
    << "; targetY " << targetY
    << "; targetZoom " << targetZoom
    << "; visibleX " << visibleX
    << "; visibleY " << visibleY
    << "; visibleZoom " << visibleZoom
    << "; diffX " << diffX
    << "; zoomDif " << zoomDif
    << "; diffY" << diffY << endl;
    
    
    // reset zoom and move steps
    moveStep = defaultMoveStep;
    zoomStep = defaultZoomStep;
    
    // if there's no position change: zoom only
    if((diffX == 0) && (diffY == 0))
    {
        moveStep = 0;
        zoomStep = defaultZoomStep;
        return;
    }
    
    // if there's no zoom change: move only
    if(zoomDif == 0)
    {
        zoomStep = 0;
        moveStep = defaultMoveStep;
        return;
    }
    
    // both zoom and position need to be uptdated
    // get the longest distance (vertical vs horizontal)
    float longestDistance;
    
    if(diffX >= diffY)  longestDistance = diffX;
    else                longestDistance = diffY;
    
    // make moveStep proportional to zoomStep
    if(zoomDif > longestDistance)
    {
        moveStep = (zoomDif / longestDistance) * zoomStep;
    }
    else
    {
        moveStep = (longestDistance / zoomDif) * zoomStep;
    }
    cout << "zoomStep " << zoomStep << " moveStep " << moveStep << endl;
}


//--------------------------------------------------------------
void player::draw()
{
    ofBackground(0,0,0);
    if(currNode != NULL && currNode->isLoaded())    
        currNode->draw(visibleRegionOfInterest->getX(), 
                       visibleRegionOfInterest->getY(), 
                       visibleRegionOfInterest->getWidth(), 
                       visibleRegionOfInterest->getHeight());
    kinect.draw();
    
}

void player::gestureListener(gesture & g)
{
    if(g.gesture_name == "Click")
    {
        cout << g.gesture_position.x << "," << g.gesture_position.y << endl;
    }
}

void player::setup()
{
    stopKinect = true;
    
    kinect.setup();
    ofAddListener(kinect.recordGestures.gestureRecognized, this, &player::gestureListener);
    
    this->currNode = NULL;
    
    
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
	}
    
    imageRegion* reg0 = new imageRegion(0,0,ofGetWidth(),ofGetHeight(),100);
    imageRegion* reg1 = new imageRegion(0,-400,200,100,400);
    imageRegion* reg2 = new imageRegion(-1000,-400,200,100,400);
    imageRegion* reg3 = new imageRegion(-2800,-400,200,100,400);
    imageRegion* reg4 = new imageRegion(-3600,-400,200,100,400);
    
    regionsOfInterest.push_back(*reg0);
    regionsOfInterest.push_back(*reg1);
    regionsOfInterest.push_back(*reg2);
    regionsOfInterest.push_back(*reg3);
    regionsOfInterest.push_back(*reg4);
    
    this->currRegionOfInterest = &regionsOfInterest.front();
    this->visibleRegionOfInterest = new imageRegion(0,0,ofGetWidth(),ofGetHeight(),100);
    
    it = regionsOfInterest.begin();
    
    // zoom out zone
    kinectZone* zone1 = new kinectZone(0, 1000, 3000, 3800);
    zone1->setImageRegion(reg0);
    kinectZone* zone2 = new kinectZone(133, 233, 0, 2900);
    zone2->setImageRegion(reg1);
    kinectZone* zone3 = new kinectZone(284, 384, 0, 2900);    
    zone3->setImageRegion(reg2);
    kinectZone* zone4 = new kinectZone(447, 547, 0, 2900);    
    zone4->setImageRegion(reg3);
    kinectZone* zone5 = new kinectZone(564, 664, 0, 2900);    
    zone5->setImageRegion(reg4);
    
    kinectZones.push_back(*zone1);
    kinectZones.push_back(*zone2);
    kinectZones.push_back(*zone3);
    kinectZones.push_back(*zone4);
    kinectZones.push_back(*zone5);
    
    
    // init variables
    
    this->defaultZoomStep = 5.0;
    this->defaultMoveStep = 10.0;
    
    this->zoomStep = defaultZoomStep;
    this->moveStep = defaultMoveStep;

    
    loadNode(11590);
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
    int id = 0;
    
    switch(key)
    {
        case OF_KEY_PAGE_UP:
        case OF_KEY_UP:    
        case OF_KEY_LEFT:
            id = currNode->getAdjacentNode("LEFT");
            break;
        case OF_KEY_PAGE_DOWN:
        case OF_KEY_DOWN:            
        case OF_KEY_RIGHT:
            id = currNode->getAdjacentNode("RIGHT");
            break;
        /*    
        case OF_KEY_UP:
            id = currNode->getAdjacentNode("UP");
            break;

            id = currNode->getAdjacentNode("DOWN");
            break;
        */
        case '.':
            stopKinect = !stopKinect;
            break;
    }
    
    
    map<int,node>::iterator iter = nodes.find(id);
    
    if(iter != nodes.end())
    {
        loadNode(id);
    }
    
    kinect.keyPressed(key);
}

//--------------------------------------------------------------
void player::keyReleased(int key){
    
}

