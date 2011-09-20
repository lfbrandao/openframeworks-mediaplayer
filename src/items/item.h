#pragma once

#include "ofMain.h"

enum itemType {VIDEO,AUDIO,IMAGE};

class item
{
public:
    item();
    item(int id, string originalURI, string itemType);
    item(int id, string originalURI, string localURI, string itemType);
    
    string getLocalURI();
    string getOriginalURI();
    string getItemType();
    int getId();
    
private:
    int id;
    string itType;
    string text;
    string title;
    string localURI;
    string originalURI;
};
