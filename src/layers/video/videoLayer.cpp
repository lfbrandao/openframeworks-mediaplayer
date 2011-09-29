#include "videoLayer.h"

//--------------------------------------------------------------
void videoLayer::setup(string videoURI)
{    
	ofBackground(0,0,0);
	frameByframe = false;
    
    this->objectURI = videoURI;
    this->playing = false;
}

void videoLayer::load()
{
    if(!loaded)
    {
        this->playing = false;
        this->videoPlayer.loadMovie(this->objectURI);
        
        this->width = ofGetWidth() * configWidth / 100;
        this->height = ofGetHeight() * configHeight / 100;
    
        //this->videoPlayer.setFrame((int)(inTime * videoPlayer.getTotalNumFrames() / videoPlayer.getDuration()));
        this->loaded = true;
    }
}

void videoLayer::unload()
{
    this->videoPlayer.stop();
    this->loaded = false;
    this->playing = false;
}

void videoLayer::play()
{
    if(!playing)
    {
        this->videoPlayer.play();
        this->videoPlayer.setPosition(inTime / videoPlayer.getDuration());
        this->playing = true;
    }
}

void videoLayer::pause()
{
    this->videoPlayer.setPaused(true);
}

void videoLayer::stop()
{
    this->videoPlayer.stop();
    this->playing = false;
}


void videoLayer::update()
{
    this->videoPlayer.idleMovie();
}

//--------------------------------------------------------------
void videoLayer::draw()
{
    ofSetHexColor(0xFFFFFF);
    videoPlayer.draw(this->x,this->y, this->width, this->height);
}

float videoLayer::getDuration()
{
    return videoPlayer.getDuration() * 1000;
}
