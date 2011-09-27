#ifndef _TEST_APP
#define _TEST_APP

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"

class kinectControllerSimple
{

public:
	void setup();
	void update();
	void draw();

	void	setupRecording(string _filename = "");
	string	generateFileName();

	bool				isTracking, isCloud, isCPBkgnd, isMasking;
	bool				isTrackingHands, isFiltering;

	ofxOpenNIContext	recordContext;
	ofxDepthGenerator	recordDepth;
	ofxImageGenerator	recordImage;
	ofxHandGenerator	recordHandTracker;
	ofxUserGenerator	recordUser;
	ofxOpenNIRecorder	oniRecorder;

	ofxHardwareDriver	hardware;

	void				drawMasks();
	void				drawPointCloud(ofxUserGenerator * user_generator, int userID);

	int					nearThreshold, farThreshold;
	int					pointCloudRotationY;

	ofImage				allUserMasks, user1Mask, user2Mask, depthRangeMask;

	float				filterFactor;

};

#endif
