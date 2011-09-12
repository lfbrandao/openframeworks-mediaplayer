#pragma once

#include "videoLayer.h"
#include <list>
#include <iterator>
#include "ofMain.h"

class node
{
public:
    node();
    void addLayer(videoLayer &vlayer);
    
    void update();
    void draw();

    void play();
    
    float getDuration();
private:
    list<layer*> layers;
    int startTime;
    float duration;
};
