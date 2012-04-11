//
//  Strings.h
//  VisualStudy
//
//  Created by Akira Hayasaka on 4/9/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef VisualStudy_NoisyString_h
#define VisualStudy_NoisyString_h

#include "ofMain.h"
#include "ofxFadable.h"

static const int max_pts_num = 350;

class NoisyString : public ofxFadableBase
{
public:
    
    void setup()
    {
        for (int i = 0; i < 1; i++)
        {
            if (i == 0)
            {
                ofPoint p(0,0,0);
                pts.push_back(p);
            }
            else
            {
                ofPoint base = pts.at(i-1);
                ofPoint p(base.x + ofNoise(i * ofRandom(0.9)) * ofRandom(-50, 50),
                          base.y + ofNoise(i * ofRandom(0.9)) * ofRandom(-50, 50),
                          base.z + ofNoise(i * ofRandom(0.9)) * ofRandom(-50, 50));
                pts.push_back(p);
            }
        }
        
        init();
        setAlpha(0.8);
        fadeOut();
        setFadeMillis(ofRandom(50, 200));
        bNeedCalc = true;
    }
    
    void update()
    {
        if (bNeedCalc)
        {
            if (pts.size() < max_pts_num)
            {
                for (int i = 0; i < 50; i++)
                {
                    ofPoint base = pts.at(pts.size()-1);
                    ofPoint p(base.x + ofNoise(pts.size() * ofRandom(0.9)) * ofRandom(-50, 50),
                              base.y + ofNoise(pts.size() * ofRandom(0.9)) * ofRandom(-50, 50),
                              base.z + ofNoise(pts.size() * ofRandom(0.9)) * ofRandom(-50, 50));
                    pts.push_back(p);            
                }
            }
            else 
            {
                updateFade();
                if (0.0 >= getAlpha()) 
                    bNeedCalc = false;
            }
            
            for (int i = 0; i < pts.size(); i++)
            {
                pts.at(i) = ofPoint(pts.at(i).x + ofNoise(i * ofRandom(0.9)) * ofRandom(-2.5, 2.5),
                                    pts.at(i).y + ofNoise(i * ofRandom(0.9)) * ofRandom(-2.5, 2.5),
                                    pts.at(i).z + ofNoise(i * ofRandom(0.9)) * ofRandom(-2.5, 2.5));
            }
        }
    }
    
    void debugDraw()
    {
        ofPushStyle();
        ofSetColor(ofColor::black);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < pts.size(); i++)
        {
            glVertex3f(pts.at(i).x, pts.at(i).y, pts.at(i).z);
        }
        glEnd();
        ofPopStyle();
    }
    
	virtual void draw(float x, float y){
        if (bNeedCalc)
        {
            if(alpha <= 0.0f)return;
            glColor4f(0.0f, 0.0f, 0.0f, alpha);
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < pts.size(); i++)
            {
                glVertex3f(pts.at(i).x, pts.at(i).y, pts.at(i).z);
            }
            glEnd();
        }
	} 
    
private:
    vector<ofPoint> pts;
    bool bNeedCalc;
};


class NoisySphere
{
public:
    
    void setup()
    {
        for (int i = 0; i < 4; i++)
        {
            NoisyString strs;
            strs.setup();
            strings.push_back(strs);
        }        
    }
    
    void update()
    {
        for (int i = 0; i < strings.size(); i++)
        {
            strings.at(i).update();
        }
    }
    
    void debugDraw()
    {
        for (int i = 0; i < strings.size(); i++)
        {
            strings.at(i).debugDraw();
        }
    }   
    
    void draw()
    {
        for (int i = 0; i < strings.size(); i++)
        {
            strings.at(i).draw(0,0);
        }
    }     
    
private:
    vector<NoisyString> strings;
    
};

#endif






