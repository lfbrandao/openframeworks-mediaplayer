#include "node.h"

node::node(){}

node::node(int id){this->id = id;}

void node::load()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->load();
    }
    this->playing = false;
    this->loaded = true;
}


void node::resize(int percentage)
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->resize(percentage);
    }
}

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

void node::draw(float x, float y, float w, float h)
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->draw(x,y,w,h);
    }
}


void node::play()
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        (*i)->play();
    }
    playing = true;
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

set<int> node::getLayersId()
{
    set<int> v;
    
    cout << "layers on node " << this->id << ": ";
    for(list<layerPtr>::iterator it = layers.begin(); it != layers.end(); ++it) 
    {
        v.insert((*it)->getId());
        cout << (*it)->getId() << " ";
    }
    cout << endl;
    
    return v;
}

void node::unload(set<int> layersToKeep)
{
    list<layerPtr>::iterator i;
    
    for (i = layers.begin(); i != layers.end(); ++i)
    {
        if(layersToKeep.count((*i)->getId()) == 0)
        {
            (*i)->unload();
        }
    }

}
