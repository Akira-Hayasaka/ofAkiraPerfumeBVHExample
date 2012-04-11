/*
 *  ofxFadableImg.h
 *  ofxFadable
 *
 *  Created by Makira on 11/06/02.
 *  Copyright 2011 yesMAYBEno. All rights reserved.
 *
 */

#pragma once

#include "ofxFadableBase.h"

class ofxFadableImg : public ofxFadableBase, public ofImage {

public:
	
	void draw(float x, float y) {
		ofPushStyle();
		if(alpha <= 0.0f)return;
		glColor4f(1.0f, 1.0f, 1.0f, alpha);		
		ofImage::draw(x, y);
		ofPopStyle();
	}

};