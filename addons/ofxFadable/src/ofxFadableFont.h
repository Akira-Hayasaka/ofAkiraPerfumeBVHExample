/*
 *  ofxFadableFont.h
 *  HeartBeat
 *
 *  Created by Makira on 11/07/03.
 *  Copyright 2011 ・‥…―━━━―…‥・yesMAYBEno・‥…―━━━―…‥・. All rights reserved.
 *
 */

#pragma once

#include "ofxFadableBase.h"

class ofxFadableFont : public ofxFadableBase, public ofTrueTypeFont {
	
public:
	
	void drawString(string s, float x, float y, ofColor c) {
		ofPushStyle();
		if(alpha <= 0.0f)return;
		float a = ofMap(alpha, 0.0, 1.0, 0, 255);		
		ofSetColor(c.r, c.g, c.b, a);
		ofTrueTypeFont::drawString(s, x, y);
		ofPopStyle();
	}
	
};