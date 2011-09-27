#include "kinectControllerSimple.h"

//--------------------------------------------------------------
void kinectControllerSimple::setup() 
{
	isTracking		= true;
	isTrackingHands	= true;
	isFiltering		= false;
	isCloud			= false;
	isCPBkgnd		= true;
	isMasking		= true;

	nearThreshold = 500;
	farThreshold  = 1000;

	filterFactor = 0.1f;

	setupRecording();

	ofBackground(0, 0, 0);
}

void kinectControllerSimple::setupRecording(string _filename) 
{
	hardware.setup();				// libusb direct control of motor, LED and accelerometers
	hardware.setLedOption(LED_OFF); // turn off the led just for yacks (or for live installation/performances ;-)
    
	recordContext.setup();	// all nodes created by code -> NOT using the xml config file at all
	//recordContext.setupUsingXMLFile();
	recordDepth.setup(&recordContext);
	recordImage.setup(&recordContext);
  
	recordUser.setup(&recordContext);
	recordUser.setSmoothing(filterFactor);				// built in openni skeleton smoothing...
	recordUser.setUseMaskPixels(isMasking);
	recordUser.setUseCloudPoints(isCloud);
	recordUser.setMaxNumberOfUsers(1);					// use this to set dynamic max number of users (NB: that a hard upper limit is defined by MAX_NUMBER_USERS in ofxUserGenerator)

	recordHandTracker.setup(&recordContext, 4);
	recordHandTracker.setSmoothing(filterFactor);		// built in openni hand track smoothing...
	recordHandTracker.setFilterFactors(filterFactor);	// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with

	/*
    recordContext.toggleRegisterViewport();
	recordContext.toggleMirror();
    oniRecorder.setup(&recordContext, ONI_STREAMING);
	*/
    
    //oniRecorder.setup(&recordContext, ONI_CYCLIC, 60);
	//read the warning in ofxOpenNIRecorder about memory usage with ONI_CYCLIC recording!!!
}

void kinectControllerSimple::update(){
    
	hardware.update();
    // update all nodes
    recordContext.update();
    //recordDepth.update();
    //recordImage.update();
    
    // demo getting depth pixels directly from depth gen
    /*
    depthRangeMask.setFromPixels(recordDepth.getDepthPixels(nearThreshold, farThreshold),
                                 recordDepth.getWidth(), recordDepth.getHeight(), OF_IMAGE_GRAYSCALE);
    */
    // update tracking/recording nodes
    if (isTracking) recordUser.update();
    /*
    // demo getting pixels from user gen
    if (isTracking && isMasking) {
        allUserMasks.setFromPixels(recordUser.getUserPixels(), recordUser.getWidth(), recordUser.getHeight(), OF_IMAGE_GRAYSCALE);
        user1Mask.setFromPixels(recordUser.getUserPixels(1), recordUser.getWidth(), recordUser.getHeight(), OF_IMAGE_GRAYSCALE);
        user2Mask.setFromPixels(recordUser.getUserPixels(2), recordUser.getWidth(), recordUser.getHeight(), OF_IMAGE_GRAYSCALE);
    }
    */
}

//--------------------------------------------------------------
void kinectControllerSimple::draw(){
    
	recordDepth.draw(0,0,640,480);
    recordImage.draw(640, 0, 640, 480);
    /*
    depthRangeMask.draw(0, 480, 320, 240);	// can use this with openCV to make masks, find contours etc when not dealing with openNI 'User' like objects
    
    if (isTracking) {
        recordUser.draw();
        
        if (isMasking) drawMasks();
        if (isCloud) drawPointCloud(&recordUser, 1);	// 0 gives you all point clouds; use userID to see point clouds for specific users
        
    }
    if (isTrackingHands)
        recordHandTracker.drawHands();
    
	glPopMatrix();
    
	ofSetColor(255, 255, 0);
    
	string statusFilter		= (string)(isFiltering ? "FILTERING" : "NOT FILTERING");
	string statusFilterLvl	= ofToString(filterFactor);
	string statusMask		= (string)(!isMasking ? "HIDE" : (isTracking ? "SHOW" : "YOU NEED TO TURN ON TRACKING!!"));
	string statusCloud		= (string)(isCloud ? "ON" : "OFF");
	string statusCloudData	= (string)(isCPBkgnd ? "SHOW BACKGROUND" : (isTracking ? "SHOW USER" : "YOU NEED TO TURN ON TRACKING!!"));
    
	string statusHardware;
    
	ofPoint statusAccelerometers = hardware.getAccelerometers();
	stringstream	statusHardwareStream;
    
	statusHardwareStream
	<< "ACCELEROMETERS:"
	<< " TILT: " << hardware.getTiltAngle() << "/" << hardware.tilt_angle
	<< " x - " << statusAccelerometers.x
	<< " y - " << statusAccelerometers.y
	<< " z - " << statusAccelerometers.z;
    
	statusHardware = statusHardwareStream.str();
    
	stringstream msg;
    
    int w = recordUser.getWidth();
    int h = recordUser.getHeight();
    ofPoint pos = recordUser.getWorldCoordinateAt(w / 2, h / 2, 0);
    
	msg
    << "    user coordinates          : " << pos.x << "," << pos.y << "," << pos.z << " h: " << h << " w: " << w << endl
	<< "    f : filter hands (custom) : " << statusFilter << endl
	<< "[ / ] : filter hands factor   : " << statusFilterLvl << endl
	<< "    m : drawing masks         : " << statusMask << endl
	<< "    c : draw cloud points     : " << statusCloud << endl
	<< "    b : cloud user data       : " << statusCloudData << endl
	<< "- / + : nearThreshold         : " << ofToString(nearThreshold) << endl
	<< "< / > : farThreshold          : " << ofToString(farThreshold) << endl
	<< endl
	//<< "File  : " << oniRecorder.getCurrentFileName() << endl
	<< "FPS   : " << ofToString(ofGetFrameRate()) << "  " << statusHardware << endl;
    
	ofDrawBitmapString(msg.str(), 20, 540);
    */
}

string kinectControllerSimple::generateFileName() {

	string _root = "kinectRecord";

	string _timestamp = ofToString(ofGetDay()) +
	ofToString(ofGetMonth()) +
	ofToString(ofGetYear()) +
	ofToString(ofGetHours()) +
	ofToString(ofGetMinutes()) +
	ofToString(ofGetSeconds());

	string _filename = (_root + _timestamp + ".oni");

	return _filename;

}
