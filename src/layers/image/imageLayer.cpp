#include "imageLayer.h"

//--------------------------------------------------------------
void imageLayer::setup(string imageURI)
{    
	ofBackground(0,0,0);
	frameByframe = false;
    this->objectURI = imageURI;
    this->loaded = false;
}

void imageLayer::load()
{
    if(!loaded)
    {
        this->img.loadImage(this->objectURI);
        
        this->width = ofGetWidth() * configWidth / 100;
        this->height = ofGetHeight() * configHeight / 100;
        
        this->loaded = true;
    }
}

void imageLayer::unload()
{
    this->img.clear();
    this->loaded = false;
}

void imageLayer::update()
{
    ofBackground(0);	
}

//--------------------------------------------------------------
void imageLayer::draw()
{
    
    if(this->opacity < 1)
    {
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,(int)(this->opacity * 255));
    }
    img.draw(this->x,this->y, this->width, this->height);
    ofDisableAlphaBlending();
}