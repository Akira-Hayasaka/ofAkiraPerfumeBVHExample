/* 
 * Copyright (c) 2009, Rui Madeira
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * http://creativecommons.org/licenses/LGPL/2.1/
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "ofxFadableBase.h"

ofxFadableBase::ofxFadableBase(){
	bFadeIn = false;
	bFadeOut = false;
	bBeginFade = false;
	alpha = 1.0f;
	fadeMillis = DEFAULT_FADE_MILLIS;
	ofEnableAlphaBlending();
}

ofxFadableBase::~ofxFadableBase(){
	
}

void ofxFadableBase::init() {
	bFadeIn = false;
	bFadeOut = false;
	bBeginFade = false;
	alpha = 1.0f;
	fadeMillis = DEFAULT_FADE_MILLIS;
	ofEnableAlphaBlending();	
}

void ofxFadableBase::updateFade(){
	unsigned long _currentTime = ofGetSystemTime();
	updateFade(_currentTime);
}

void ofxFadableBase::updateFade(unsigned long& currentTime){
	if(bBeginFade){
		bBeginFade = false;
		timeStartFade = currentTime;
		if(bFadeIn)timeEndFade = currentTime + (unsigned long)((1.0f - alpha) * fadeMillis);
		else timeEndFade = currentTime + (unsigned long)(alpha*fadeMillis);
		if(timeEndFade == currentTime){
			if(bFadeIn){
				bFadeIn = false;
				alpha = 1.0f;
			} else {
				bFadeOut = false;
				alpha = 0.0f;
			}
		}
	}
	if(bFadeIn){
		alpha = 1.0f - ((float)(timeEndFade - currentTime)) / (float)fadeMillis;
		if(currentTime > timeEndFade){
			bFadeIn = false;
			alpha = 1.0f;
		}
	} else if(bFadeOut){
		alpha = (float)(timeEndFade - currentTime) / (float)fadeMillis;
		if(currentTime > timeEndFade){
			bFadeIn = false;
			alpha = 0.0f;
		}
	}
}

void ofxFadableBase::fadeIn(){
	if(bFadeIn)return;
	if(alpha == 1.0f) return;
	bBeginFade = true;
	bFadeIn = true;
	bFadeOut = false;
}

void ofxFadableBase::fadeOut(){
	if(bFadeOut)return;
	if(alpha == 0.0f) return;
	bBeginFade = true;
	bFadeOut = true;
	bFadeIn = false;
}

bool ofxFadableBase::isFadingIn(){
	return bFadeIn;
}

bool ofxFadableBase::isFadingOut(){
	return bFadeOut;
}

void ofxFadableBase::setFadeSeconds(float _seconds){
	setFadeMillis((int)(_seconds * 1000.0f));
}

void ofxFadableBase::setFadeMillis(int _millis){
	fadeMillis = _millis;
}

float ofxFadableBase::getFadeSeconds(){
	return (float)fadeMillis * 0.001f;
}

int ofxFadableBase::getFadeMillis(){
	return fadeMillis;
}

void ofxFadableBase::setAlpha(float _a){
	alpha = _a;
}

float ofxFadableBase::getAlpha(){
	return alpha;
}

void ofxFadableBase::stopFade(){
	bBeginFade = bFadeIn = bFadeOut = false;
}



