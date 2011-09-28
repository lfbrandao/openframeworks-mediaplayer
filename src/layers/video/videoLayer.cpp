#include "videoLayer.h"

//--------------------------------------------------------------
void videoLayer::setup(string videoURI)
{    
	ofBackground(0,0,0);
	frameByframe = false;
    
    this->objectURI = videoURI;
}

void videoLayer::load()
{
    if(!loaded)
    {
        this->videoPlayer.loadMovie(this->objectURI);
        if(this->width == 100)
        {
            this->width = width;
            this->height = (ofGetWidth() * videoPlayer.getHeight() / videoPlayer.getWidth());
            this->width = ofGetWidth();
        }
        else
        {
            this->width = this->videoPlayer.width * this->width / 100;
            this->height = this->videoPlayer.height * this->height / 100;
        }
        
        this->loaded = true;
    }
}

void videoLayer::play()
{
    videoPlayer.setVolume(50);
    this->videoPlayer.play();    
}

void videoLayer::pause()
{
    this->videoPlayer.setPaused(true);
}

void videoLayer::stop()
{
    this->videoPlayer.stop();
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
