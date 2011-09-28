#pragma once

#include "videoLayer.h"
#include "ofMain.h"
#include <iterator>
#include <list>
#include <map>
#include <set>

typedef tr1::shared_ptr<layer> layerPtr;

class node
{
public:
    node();
    node(int id);
    void addLayer(layerPtr vlayer);
    
    void update();
    void draw();
    void draw(float x, float y, float w, float h);
    void load();
    
    void play();
    void pause();
    void stop();
    
    void resize(int percentage);
    
    int getAdjacentNode(string direction);
    void addAdjacentNode(string direction, int nodeId);
    map<string,int> getAdjacentNodes() { return this->adjacentNodes; }
    
    int getId(){return this->id;}
    int setId(int id){this->id = id;}
    
    void unload(set<int> layersToKeep);
    
    set<int> getLayersId();    
    bool isLoaded(){return loaded;}
    bool isPlaying(){return playing;}
    
private:
    int id;
    list<layerPtr> layers;
    map<string, int> adjacentNodes;
    bool loaded;
    bool playing;
};
