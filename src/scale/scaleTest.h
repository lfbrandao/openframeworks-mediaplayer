#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "videoLayer.h"
#include "node.h"

class scaleTest : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		
		ofTrueTypeFont  font;
		string title, date, byline;
		string trend;
		string location, city;
	
	
		ofxJSONElement nyt;
		ofxJSONElement twitter;
		string timestamp;
		ofxJSONElement flickr;
		ofxJSONElement facebook;;
    
    videoLayer videoPlayer;
    videoLayer videoLayer2;
    videoLayer videoLayer3;
    videoLayer videoLayer4;
    videoLayer videoLayer5;
    bool frameByframe;
    node testNode;
    list<node> nodes; 
    int scale;
	
};