#include "item.h"

item::item()
{
}

item::item(int id, string originalURI, string itemType)
{
    this->id = id;
    this->originalURI = originalURI;
    this->itType = itemType;
}

item::item(int id, string originalURI, string localURI, string itemType)
{
    this->id = id;
    this->localURI = localURI;
    this->originalURI = originalURI;
    this->itType = itemType;
}

string item::getLocalURI()
{
    return this->localURI;
}

string item::getOriginalURI()
{
    return this->originalURI;
}

string item::getItemType()
{
    return this->itType;        
}

int item::getId()
{
    return this->id;    
}
