#include "audioLayer.h"

//--------------------------------------------------------------
void audioLayer::setup(string audioURI)
{    
	ofBackground(0,0,0);
    this->objectURI = audioURI;
    this->loaded = false;
}

void audioLayer::load()
{
    if(!loaded)
    {
        this->soundPlayer.loadSound(this->objectURI);
        this->loaded = true;
        this->playing = false;
    }
}

void audioLayer::unload()
{
    this->playing = false;
    this->soundPlayer.stop();
}

void audioLayer::play()
{
    if(!playing)
    {
        this->soundPlayer.play();
        //this->soundPlayer.setPosition(inTime / soundPlayer.length);
        this->playing = true;
    }
}

void audioLayer::pause()
{
    this->soundPlayer.setPaused(true);
}

void audioLayer::stop()
{
    this->soundPlayer.stop();
    this->playing = false;
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
