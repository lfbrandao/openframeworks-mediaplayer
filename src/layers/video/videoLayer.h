#pragma once

#include "ofMain.h"
#include <stdio.h>

class videoLayer
{
public:
    void setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt);
    void play();
    void pause();
    void stop();
    ofVideoPlayer 		videoPlayer;
    bool                frameByframe;
    
    // of methods
    void update();
    void draw();
private:
    int x;
    int y;
    int width;
    int height;
};

