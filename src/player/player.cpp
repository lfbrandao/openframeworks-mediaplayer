#include "player.h"

//--------------------------------------------------------------
void player::setup()
{
	ofBackground(255,255,255);

	frameByframe = true;

	videoPlayer.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", ofGetWidth(), ofGetHeight(), 0, 0, 0, 0);
    videoPlayer.play();
}

//--------------------------------------------------------------
void player::update()
{
    videoPlayer.update();
}

//--------------------------------------------------------------
void player::draw()
{
    videoPlayer.draw();
}