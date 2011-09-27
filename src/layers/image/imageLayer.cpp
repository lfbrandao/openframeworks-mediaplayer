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
    cout << "loading " << objectURI << endl;
    this->img.loadImage(this->objectURI);
    this->loaded = true;
}

void imageLayer::update()
{
    ofBackground(255);	
}

//--------------------------------------------------------------
void imageLayer::draw()
{
    cout << "drawing image " << "x" << x << "y" << y << "width" << width << "height" << height << endl; 
    img.draw(this->x,this->y, this->width, this->height);
}