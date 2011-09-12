#include "node.h"

node::node(){}

void node::addLayer(videoLayer layer)
{
    layers.push_back(layer);
    
    if(layer.getDuration() > this->duration)
    {
        this->duration = layer.getDuration();
    }
}

void node::update()
{
    list<videoLayer>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        i->update();
    }   
}

void node::draw()
{
    list<videoLayer>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        i->draw();
    }
}


void node::play()
{
    startTime = ofGetElapsedTimeMillis();
    
    list<videoLayer>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        i->play();
    }
}

float node::getDuration()
{
    return this->duration;
}