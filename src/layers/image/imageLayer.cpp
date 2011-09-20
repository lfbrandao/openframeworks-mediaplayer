#include "imageLayer.h"

//--------------------------------------------------------------
void imageLayer::setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt)
{    
	ofBackground(255,255,255);
	frameByframe = false;
    
	this->img.loadImage(videoURI);
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    
    printf("Width %i \n", width);
    printf("Height %i \n", height);
    printf("X %i \n", x);
    printf("Y %i \n", y);
}

void imageLayer::setup(string videoURI, int startAt, int stopAt)
{
    this->img.loadImage(videoURI);
}

void imageLayer::play()
{
}

void imageLayer::pause()
{
}

void imageLayer::stop()
{
}


void imageLayer::update()
{
    ofBackground(255);	
}

//--------------------------------------------------------------
void imageLayer::draw()
{
    img.draw(this->x,this->y, this->width, this->height);
    //img.draw(0, 0);
}

float imageLayer::getDuration()
{

}
