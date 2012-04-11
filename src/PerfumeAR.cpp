#include "PerfumeAR.h"

void PerfumeAR::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);    
    
    bDebug = false;
    arCam.setup(ofGetWidth(), ofGetHeight());
    
    perfume.setup();
    
    // para tracks
    vector<string> fs;
    fs.push_back("para_audio_wav/perhp_Bass-Acbass.wav");
    fs.push_back("para_audio_wav/perhp_Snare-White.wav");
    aMgr.setup(fs, false);
    
    tvis.setup(aMgr.getSoundTracks());    
}

void PerfumeAR::update()
{
    arCam.update();
    perfume.update();
    aMgr.update();
    tvis.update();
}

void PerfumeAR::draw()
{
    arCam.draw();
    perfume.draw(arCam.getARTK(), tvis);
    
    if (bDebug)
    {
        arCam.debugDraw();
    }
}

void PerfumeAR::keyPressed(int key)
{
    if (key == 'd')
    {
        bDebug = !bDebug;
    }
}

void PerfumeAR::keyReleased(int key){}
void PerfumeAR::mouseMoved(int x, int y ){}
void PerfumeAR::mouseDragged(int x, int y, int button){}
void PerfumeAR::mousePressed(int x, int y, int button){}
void PerfumeAR::mouseReleased(int x, int y, int button){}
void PerfumeAR::windowResized(int w, int h){}
void PerfumeAR::gotMessage(ofMessage msg){}
void PerfumeAR::dragEvent(ofDragInfo dragInfo){}