#pragma once

#include "videoLayer.h"
#include "ofMain.h"
#include <iterator>
#include <list>
#include <map>

typedef tr1::shared_ptr<layer> layerPtr;

class node
{
public:
    node();
    node(int id);
    void addLayer(layerPtr vlayer);
    
    void update();
    void draw();

    void play();
    void pause();
    void stop();
    
    int getAdjacentNode(string direction);
    void addAdjacentNode(string direction, int nodeId);

    int getId(){return this->id;}
    int setId(int id){this->id = id;}
    
private:
    int id;
    list<layerPtr> layers;
    map<string, int> adjacentNodes;
};
