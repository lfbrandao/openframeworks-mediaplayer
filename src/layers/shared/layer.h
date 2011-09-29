#pragma once
#include <iostream>

class layer 
{
    public:
        virtual void setup(string objectURI) = 0;
        
        virtual void load() = 0;
        
        // playback control
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
    
        // of methods
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void unload() = 0;
    
        virtual ~layer(){}
        
        // setters & getters
        int getId(){return id;}
        int getX(){return x;}
        int getY(){return y;}
        int getHeight(){return height;}
        int getWidth(){return width;}
        float getVolume(){return volume;}
        float getInTime(){return inTime;}
        float getOutTime(){return outTime;}
        float getOpacity(){return opacity;}
        float getAspectRatio(){return aspectRatio;}
        
        void  setId(int id){this->id = id;}
        void  setX(int x){this->x = ofGetWidth() * x / 100;}
        void  setY(int y){this->y = ofGetHeight() * y / 100;}
    void  setHeight(int height){this->height = height; configHeight = height;}
    void  setWidth(int width){this->width = width; configWidth = width;}
        void  setVolume(float volume){this->volume = volume;}    
        void  setInTime(float inTime){this->inTime = inTime;}    
    void  setOutTime(float outTime){this->outTime = outTime; outTimeConfig = outTime;}    
        void  setOpacity(float opacity){this->opacity = opacity;}    
        void  setAspectRatio(float aspectRatio){this->aspectRatio = aspectRatio;}
        
        void  resize(int percentage) 
        {
            /*float newWidth = originalWidth * percentage / 100;
            float newHeight = originalHeight * percentage / 100;
            float xPosOffset = (width - newWidth) / 2;
            float yPosOffset = (height - newHeight) / 2;
            
            if(newWidth >= originalWidth)
            {
                this->width = originalWidth * percentage / 100;
                this->height = originalHeight * percentage / 100;
                this->x = x + xPosOffset;
                this->y = y + yPosOffset;
            }*/
        }
    protected:
        string objectURI;
        int id;
        int x;
        int y;
        int height, configHeight;
        int width, configWidth;
        float volume;
        float inTime;
        float outTime, outTimeConfig;
        float opacity;
        float aspectRatio;
    bool loaded;
    bool playing;
};