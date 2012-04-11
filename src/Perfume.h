//
//  Perfume.h
//  PerfumeAR
//
//  Created by Akira Hayasaka on 3/24/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef PerfumeAR_Perfume_h
#define PerfumeAR_Perfume_h

#include "ofMain.h"
#include "ofxBvh.h"
#include "ofxARToolkitPlus.h"
#include "TrackAndVisual.h"

class Perfume
{
public:
    void setup();
    void update();
    void draw(ofxARToolkitPlus artk, TrackAndVisual tvis);
    void drawBVHMotion(ofxBvh bvh);
    void keyPressed(ofKeyEventArgs& key);
    void keyReleased(ofKeyEventArgs& key);    
    
private:
	ofSoundPlayer   track;
	ofxBvh          bvh[3];    
    float           play_rate, play_rate_t;
    
    void            billboard();
};

#endif
