#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "layer.h"

class imageLayer : public layer
{
public:
    void setup(string imageURI);
    
    virtual void load();
    
    virtual void play() {};
    virtual void pause(){};
    virtual void stop() {};
    
    
    ofImage img;
    bool                frameByframe;
    
    // of methods
    virtual void update();
    virtual void draw();
    
    float getDuration();
private:
    int duration;
};

