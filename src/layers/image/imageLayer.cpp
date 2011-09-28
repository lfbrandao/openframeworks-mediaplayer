#include "imageLayer.h"

//--------------------------------------------------------------
void imageLayer::setup(string imageURI)
{    
	ofBackground(0,0,0);
	frameByframe = false;
    this->objectURI = imageURI;
    this->loaded = false;
}

void imageLayer::load()
{
    if(!loaded)
    {
        this->img.loadImage(this->objectURI);
        if(this->width == 100)
        {
            this->width = width;
            this->height = (ofGetWidth() * img.getHeight() / img.getWidth());
            this->width = ofGetWidth();
        }
        else
        {
            this->width = this->img.width * this->width / 100;
            this->height = this->img.height * this->height / 100;
        }
        
        this->loaded = true;
    }
}

void imageLayer::update()
{
    ofBackground(0);	
}

//--------------------------------------------------------------
void imageLayer::draw()
{
    img.draw(this->x,this->y, this->width, this->height);
}