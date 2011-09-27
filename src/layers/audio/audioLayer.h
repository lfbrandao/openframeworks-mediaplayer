#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "layer.h"

class audioLayer : public layer
{
public:
    audioLayer(){}
    void setup(string audioURI);
    
    virtual void load();
    virtual void play();
    virtual void pause();
    virtual void stop();
    
    ofSoundPlayer 		soundPlayer;
    
    // of methods
    virtual void update();
    virtual void draw();
    float getDuration();
private:
    int duration;
};

