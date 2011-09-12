#pragma once

#include "ofMain.h"
#include "videoLayer.h"
#include "node.h"
#include <list>

class player : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
    private:	
		videoLayer 		videoPlayer;
        videoLayer 		videoLayer2;
        videoLayer 		videoLayer3;
        videoLayer 		videoLayer4;
        videoLayer 		videoLayer5;
		bool                frameByframe;
        node testNode;  
        list<node> nodes;    
};

