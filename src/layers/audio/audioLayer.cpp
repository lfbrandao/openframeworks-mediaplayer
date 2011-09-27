#include "audioLayer.h"

//--------------------------------------------------------------
void audioLayer::setup(string audioURI)
{    
	ofBackground(0,0,0);
    this->objectURI = audioURI;
}

void audioLayer::load()
{
    this->soundPlayer.loadSound(this->objectURI);
}

void audioLayer::play()
{
    this->soundPlayer.play();    
}

void audioLayer::pause()
{
    this->soundPlayer.setPaused(true);
}

void audioLayer::stop()
{
    this->soundPlayer.stop();
}


void audioLayer::update()
{
    ofSoundUpdate();
}

//--------------------------------------------------------------
void audioLayer::draw()
{
}

float audioLayer::getDuration()
{
    return 0.0;
}
