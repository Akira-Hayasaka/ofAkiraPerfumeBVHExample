//
//  GrowingCircle.h
//  emptyExample
//
//  Created by Akira Hayasaka on 4/10/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef emptyExample_GrowingCircle_h
#define emptyExample_GrowingCircle_h

#include "ofMain.h"
#include "ofxFadable.h"

class GrowingCircle : ofxFadableBase
{
public:
    
    void setup()
    {
        circle.setArcResolution(100);
        circle.arc(ofPoint(0,0,0), 100, 100, 0, 360);  
        circle.close();  
        circle.arc(ofPoint(0,0,0), 110, 110, 0, 360); 
        scale = 0.0;
        
        init();
        fadeOut();
        setFadeMillis(2000);        
        bNeedCalc = true;
    }
    
    void update()
    {
        if (bNeedCalc)
        {        
            scale += 0.1;
            updateFade();
            if (0.0 >= getAlpha()) 
                bNeedCalc = false;            
        }
    }
    
    void debugDraw()
    {
        ofPushMatrix();
        ofScale(scale, scale, scale);
        ofRotateX(90);
        circle.draw();
        ofPopMatrix();
    }
    
	virtual void draw(float x, float y){
        if (bNeedCalc)
        {
            if(alpha <= 0.0f)return;
            circle.setFillColor(ofColor(0, 0, 0, alpha * 255));
            ofPushMatrix();
            ofScale(scale, scale, scale);
            ofRotateX(90);
            circle.draw();
            ofPopMatrix();
            glEnd();
        }
	}     
    
private:
    ofPath circle;
    float scale;
    bool bNeedCalc;
};

#endif
