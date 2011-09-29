#include "kinectController.h"

//--------------------------------------------------------------
void kinectController::setup() 
{
	isTracking		= true;
	isFiltering		= false;
	isRecording		= false;
	isCloud			= false;
	isCPBkgnd		= true;
	isMasking		= true;

    showFullBodyTracker = false;
    showHands = true;
    
	nearThreshold = 500;
	farThreshold  = 1000;
    
	filterFactor = 0.1f;
    
	setupRecording();
    
	ofBackground(0, 0, 0);
    
    myFont.loadFont("frabk.ttf", 32);
}

void kinectController::setupRecording(string _filename) 
{
	hardware.setup();				// libusb direct control of motor, LED and accelerometers
	hardware.setLedOption(LED_OFF); // turn off the led just for yacks (or for live installation/performances ;-)
    
	recordContext.setup();	// all nodes created by code -> NOT using the xml config file at all
	recordDepth.setup(&recordContext);
	recordImage.setup(&recordContext);
    
    recordUser.setup(&recordContext);
	recordUser.setSmoothing(filterFactor);				// built in openni skeleton smoothing...
	recordUser.setUseMaskPixels(isMasking);
	recordUser.setMaxNumberOfUsers(1);
    
    recordHandTracker.setup(&recordContext, 4);
	recordHandTracker.setSmoothing(filterFactor);		// built in openni hand track smoothing...
	recordHandTracker.setFilterFactors(filterFactor);
    
	recordContext.toggleRegisterViewport();
	recordContext.toggleMirror();
    
    recordGestures.setup(&recordContext);
    recordGestures.addGesture("Wave");
    recordGestures.addGesture("Swipe");
    recordGestures.addGesture("Click");
    
    //ofAddListener(recordGestures.gestureRecognized, this, &kinectController::gestureListener);
}


//--------------------------------------------------------------
void kinectController::update()
{
	hardware.update();

    // update all nodes
    recordContext.update();
    recordDepth.update();
    recordImage.update();
    
    // update tracking/recording nodes
    if (isTracking) recordUser.update();
    
    // demo getting pixels from user gen
    if (isTracking && showFullBodyTracker) 
    {
        user1Mask.setFromPixels(recordUser.getUserPixels(1), recordUser.getWidth(), recordUser.getHeight(), OF_IMAGE_GRAYSCALE);
    }
}

//--------------------------------------------------------------
void kinectController::draw(){
    glPushMatrix();
	
    if (isTracking) 
    {
        //recordUser.draw();
        if(showFullBodyTracker) drawMasks();
    }
	
	stringstream msg;
    if(showFullBodyTracker)
    {
        int i = recordUser.getNumberOfTrackedUsers();
        if(i > 0)
        {
            ofxTrackedUser * tracked = recordUser.getTrackedUser(i);
        
            if(tracked != NULL) 
            {  
                if(tracked->neck.found)
                {  
                    msg << "tracking neck " << (int)tracked->neck.position[1].X 
                        << "," << (int)tracked->neck.position[1].Y 
                        << "," << (int)tracked->neck.position[1].Z
                    << endl;
                          
                    position = tracked->neck.position[1];
                    tracking = true;
                }
            }
            else
                tracking = false;
        }
        else
        {
            msg << "not tracking" << endl; 
            tracking = false;
        }
        ofSetColor(255, 255, 255);
        myFont.drawString(msg.str(), 30, 50);
    }
    
    
    if(showHands)
    {
        if(recordHandTracker.getNumTrackedHands() > 0)
        {
            for(int i = 0; i < recordHandTracker.getNumTrackedHands(); i++)
            {    
                ofxTrackedHand* tHand = recordHandTracker.getHand(i);
                if(tHand != NULL)
                {
                    ofPoint pos = tHand->progPos;
                    ofFill();
                    
                    ofCircle(pos.x * ofGetWidth(), pos.y * ofGetHeight(), 15);
                }
            }
        }
    }
    glPopMatrix();
    
}

void kinectController:: drawMasks() 
{
	glPushMatrix();
	user1Mask.draw(ofGetWidth()-250,ofGetHeight()-170, 240, 160);
	glPopMatrix();
}

//--------------------------------------------------------------
void kinectController::keyPressed(int key){
    
	float smooth;
    
	switch (key) {            
		case 'w': // up key
			hardware.setTiltAngle(hardware.tilt_angle++);
			break;
		case 's': // down key
			hardware.setTiltAngle(hardware.tilt_angle--);
			break;
		case 't':
		case 'T':
			isTracking = !isTracking;
			break;
        case 'b':
        case 'B':
			showFullBodyTracker = !showFullBodyTracker;
			break;
        case 'h':
        case 'H':
            showHands = !showHands;
            break;
		default:
			break;
	}
}

string kinectController::generateFileName() {
    
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