#include "player.h"
/*
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
 */

//--------------------------------------------------------------
void player::setup()
{
	ofBackground(255,255,255);
    videoPlayer.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", ofGetWidth(), ofGetHeight(), 0, 0, 0, 0);
    videoLayer2.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", 200, 200, 0, 0, 0, 0);
    videoLayer3.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", 175, 175, 0, 0, 0, 0);
    videoLayer4.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", 150, 150, 0, 0, 0, 0);
    videoLayer5.setup("/Users/luisbrandao/Dropbox/Public/earthless.mp4", 125, 125, 0, 0, 0, 0);
    testNode.addLayer(videoPlayer);
    testNode.addLayer(videoLayer2);
    testNode.addLayer(videoLayer3);
    testNode.addLayer(videoLayer4);
    testNode.addLayer(videoLayer5);
    testNode.play();
}

//--------------------------------------------------------------
void player::update()
{
    testNode.update();
}

//--------------------------------------------------------------
void player::draw()
{
    testNode.draw();
}
