#pragma once

#include "videoLayer.h"
#include <list>
#include <iterator>
#include "ofMain.h"

class node
{
public:
    node();
    void addLayer(videoLayer layer);
    
    void update();
    void draw();

    void play();
    
    float getDuration();
private:
    list<videoLayer> layers;
    int startTime;
    float duration;
};
