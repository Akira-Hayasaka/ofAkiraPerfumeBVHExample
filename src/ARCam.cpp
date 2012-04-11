//
//  ARCam.cpp
//  PerfumeAR
//
//  Created by Akira Hayasaka on 3/25/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#include "ARCam.h"


void ARCam::setup(int w, int h)
{
	width = w;
	height = h;
	
	colorImage.allocate(width, height);
	grayImage.allocate(width, height);
	grayThres.allocate(width, height);
    
	artk.setup(width, height);
    
	threshold = 85;
	artk.setThreshold(threshold);
	
    camera.setup();    
    
    ofRegisterKeyEvents(this);
}

void ARCam::update()
{
    camera.update();
    
	if(camera.isFrameNew()) 
    {
		colorImage.setFromPixels(camera.getLivePixels().getPixels(), width, height);
		grayImage = colorImage;
		grayThres = grayImage;
		grayThres.threshold(threshold);
		artk.update(grayImage.getPixels());
	}
}

void ARCam::draw()
{
	ofSetHexColor(0xffffff);
	colorImage.draw(0, 0);
}

void ARCam::debugDraw()
{
    ofSetHexColor(0x666666);
	ofDrawBitmapString(ofToString(artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);
    
	artk.draw(0, 0);
    
	artk.applyProjectionMatrix();
	int numDetected = artk.getNumDetectedMarkers();
	ofEnableAlphaBlending();
	for(int i=0; i<numDetected; i++) {
        artk.applyModelMatrix(i);		
		
		ofNoFill();
		ofSetLineWidth(5);
		ofSetHexColor(0xffffff);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0); 
		glVertex3f(0, 0, 50);
		glEnd();
		
		ofNoFill();
		ofEnableSmoothing();
		ofSetColor(255, 255, 0, 50);	
		for(int i=0; i<10; i++) {		
			ofRect(-25, -25, 50, 50);
			ofTranslate(0, 0, i*1);
		}
	}  
}

void ARCam::keyPressed(ofKeyEventArgs& key)
{
	if(key.key == OF_KEY_UP) 
    {
		artk.setThreshold(++threshold);
		
	} else if (key.key == OF_KEY_DOWN) 
    {
		artk.setThreshold(--threshold);		
	}    
}

void ARCam::keyReleased(ofKeyEventArgs& key){}


