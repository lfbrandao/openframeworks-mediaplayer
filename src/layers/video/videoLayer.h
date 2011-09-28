#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "layer.h"

class videoLayer : public layer
{
public:
    virtual void setup(string videoURI);

    virtual void load();
    virtual void unload();
    
    virtual void play();
    virtual void pause();
    virtual void stop();
    
    ofVideoPlayer 		videoPlayer;
    bool                frameByframe;
    
    // of methods
    virtual void update();
    virtual void draw();
    
    float getDuration();
};

