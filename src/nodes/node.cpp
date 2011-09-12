#include "node.h"

node::node(){}

void node::addLayer(videoLayer &vlayer)
{
    
    layers.push_back((&vlayer));
    
    if((&vlayer)->getDuration() > this->duration)
    {
        this->duration = (&vlayer)->getDuration();
    }
}

void node::update()
{
    list<layer*>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->update();
    }   
}

void node::draw()
{
    list<layer*>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->draw();
    }
}


void node::play()
{
    startTime = ofGetElapsedTimeMillis();
    
    list<layer*>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->play();
    }
}

float node::getDuration()
{
    return this->duration;
}