#pragma once
#include <iostream>

class layer 
{
    public:
        virtual void setup(string videoURI, int startAt, int stopAt) = 0;
        // playback control
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
    
        // of methods
        virtual void update() = 0;
        virtual void draw() = 0;
    
        virtual ~layer(){}
};