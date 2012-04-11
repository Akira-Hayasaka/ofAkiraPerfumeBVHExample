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


#pragma once

#include "ofMain.h"

#define DEFAULT_FADE_MILLIS 1000

class ofxFadableBase{
protected:
	float alpha;
	int fadeMillis;
	unsigned long timeStartFade, timeEndFade;
	bool bBeginFade, bFadeIn, bFadeOut;
public:
	
	ofxFadableBase();
	virtual  ~ofxFadableBase();
	
	virtual void init();
	virtual void updateFade();
	virtual void updateFade(unsigned long& currentTime);
	virtual void fadeIn();
	virtual void fadeOut();
	virtual bool isFadingIn();
	virtual bool isFadingOut();
	virtual void setFadeSeconds(float _seconds);
	virtual void setFadeMillis(int _millis);
	virtual float getFadeSeconds();
	virtual int getFadeMillis();
	virtual void setAlpha(float _a);
	virtual float getAlpha();
	virtual void stopFade();
};

