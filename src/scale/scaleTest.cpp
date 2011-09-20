#include "scaleTest.h"

static string readfile(string path) 
{
}

void scaleTest::setup()
{
    ofBackground(255,255,255);
    layerPtr l = layerPtr(new videoLayer);
    l->setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", ofGetWidth(), ofGetHeight(), 0, 0, 0, 0);
    testNode.addLayer(l);
    testNode.play();
    this->scale = 100;
}

//--------------------------------------------------------------
void scaleTest::update()
{
    testNode.update();
}

//--------------------------------------------------------------
void scaleTest::draw()
{
    testNode.resize(scale);
    testNode.draw();
}

//--------------------------------------------------------------
void scaleTest::keyPressed(int key)
{
    switch(key)
    {
        case OF_KEY_LEFT:
            --scale;
            break;
        case OF_KEY_RIGHT:
            ++scale;
            break;
    }
    cout << "Scale " << scale << endl;
}

//--------------------------------------------------------------
void scaleTest::keyReleased(int key){

}

//--------------------------------------------------------------
void scaleTest::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void scaleTest::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void scaleTest::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void scaleTest::mouseReleased(int x, int y, int button){
	
	}

//--------------------------------------------------------------
void scaleTest::windowResized(int w, int h){

}

    