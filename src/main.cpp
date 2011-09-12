#include "ofMain.h"
#include "player.h"
#include "ofAppGlutWindow.h"
#include <iostream> 
using namespace std;

//========================================================================
int main( ){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 800, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new player());

}
