#pragma once

#include "ofMain.h"
#include "videoLayer.h"
#include "imageLayer.h"
#include "audioLayer.h"
#include "node.h"
#include "layer.h"
#include <map>
#include <iterator>
#include "ofxJSONElement.h"
#include <tr1/memory>
#include "kinectControllerSimple.h"

typedef tr1::shared_ptr<layer> layerPtr;

class player : public ofBaseApp
{
	public:
        player(string projectFilePath);
        
        void setupRecording(string _filename);

        //void load(string projectFilePath);
		void setup();
        void mocksetup();
		void update();
		void draw();
    private:	
        void keyPressed(int key);
        void keyReleased(int key);
        bool isItemInList(string itemId);

        node* currNode;  

        map<int,layerPtr> layers;  // list of items: <url,item>
        map<int,node> nodes;    // list of items: <url,item>
        
        ofxJSONElement  jsonProject;
    
        layerPtr createLayerForItem(string itemType, string localURI);
        string projectFilePath;
    
        kinectControllerSimple kinect;
    
        
};

