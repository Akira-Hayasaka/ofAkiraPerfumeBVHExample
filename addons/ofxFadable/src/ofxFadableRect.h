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

#include "ofxFadableBase.h"

class ofxFadableRect: public ofxFadableBase{
	float r, g, b;
public:
	ofxFadableRect(){
		r = g = b = 1.0f;
	}
	
	void setColor(int _r, int _g, int _b){ // 0 .. 255
		setUnitColor((float)_r/255.0f, (float)_g/255.0f, (float)_b/255.0f);
	}
	
	void setUnitColor(float _r, float _g, float _b){ // 0.0 .. 1.0
		r = _r;
		g = _g;
		b = _b;
	}
	
	ofColor getColor(){
		ofColor c;
		c.r = r;
		c.g = g;
		c.b = b;
		c.a = alpha;
		return c;
	}
	
	void draw(float x, float y, float w, float h){
		if(alpha <= 0.0f) return;
		glColor4f(r, g, b, alpha);
		ofRect(x, y, w, h);
	}
};

