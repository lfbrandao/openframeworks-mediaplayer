#pragma once

#include "ofMain.h"
#include "videoLayer.h"

class player : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		videoLayer 		videoPlayer;
		bool                frameByframe;
};

