#include "node.h"

node::node(){}

node::node(int id){this->id = id;}

void node::addLayer(layerPtr vlayer)
{
    layers.push_back(vlayer);
}

void node::update()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->update();
    }
}

void node::draw()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->draw();
    }
}

void node::play()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->play();
    }
}

void node::pause()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->pause();
    }
}

void node::stop()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->stop();
    }
}

int node::getAdjacentNode(string direction)
{
    map<string,int>::iterator it = adjacentNodes.find(direction);

    if(it != adjacentNodes.end())
    {
        return it->second;
    }
}

void node::addAdjacentNode(string direction, int nodeId)
{
    adjacentNodes.insert(pair<string,int>(direction,nodeId));
}