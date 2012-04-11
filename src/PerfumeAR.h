#pragma once

#include "ofMain.h"
#include "ARCam.h"
#include "Perfume.h"
#include "AudioManager.h"
#include "GrowingCircle.h"
#include "NoisyString.h"
#include "TrackAndVisual.h"

class PerfumeAR : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    bool    bDebug;    
    ARCam   arCam;
    
    Perfume perfume;
    
    AudioManager    aMgr;
    TrackAndVisual tvis;
};
