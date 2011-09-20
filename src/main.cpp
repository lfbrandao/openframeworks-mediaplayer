#include "ofMain.h"
#include "player.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include <iostream> 
#include <tr1/memory>

using namespace std;



//========================================================================
int main( )
{
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 800, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp( new player());
    ofRunApp( new player("/Users/luisbrandao/Documents/metaLAB/code/revere/zeega_project.json"));
    //videoLayer v;
    //"/Users/luisbrandao/Downloads/zeega_test_project.json"
    //ofRunApp(new testApp());
}
