//
//  ARCam.h
//  PerfumeAR
//
//  Created by Akira Hayasaka on 3/24/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef PerfumeAR_ARCam_h
#define PerfumeAR_ARCam_h

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "ofxEdsdk.h"


class ARCam
{
public:
    void setup(int w, int h);
    void update();
    void draw();
    void debugDraw();
    void keyPressed(ofKeyEventArgs& key);
    void keyReleased(ofKeyEventArgs& key);
    
    ofxARToolkitPlus getARTK()
    {
        return artk;
    }

private:
    int                 width, height;
    
    ofxEdsdk::Camera    camera;
	
    ofxARToolkitPlus    artk;	
    int                 threshold;
    ofxCvColorImage     colorImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage	grayThres;    
    
};

#endif
