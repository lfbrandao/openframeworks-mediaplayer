#ifndef _TEST_APP
#define _TEST_APP

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"


class kinectController{
    
public:
	void setup();
	void update();
	void draw();
    
	void keyPressed  (int key);
    
	void	setupRecording(string _filename = "");
	void	setupPlayback(string _filename);
	string	generateFileName();
    
    void gestureListener(gesture & g);
    
    
	bool				isTracking, isRecording, isCloud, isCPBkgnd, isMasking;
	bool				isFiltering;
    
	ofxOpenNIContext	recordContext;
	ofxDepthGenerator	recordDepth;
    
	ofxImageGenerator	recordImage;
	ofxUserGenerator	recordUser;
    ofxHandGenerator	recordHandTracker;
    ofxGestureGenerator recordGestures;
	ofxHardwareDriver	hardware;
    
	void				drawMasks();
	
	int					nearThreshold, farThreshold;
	int					pointCloudRotationY;
    
	ofImage				user1Mask;
    
	float				filterFactor;
    
    XnPoint3D position;
    bool tracking;
    
    ofTrueTypeFont      myFont;
};

#endif
