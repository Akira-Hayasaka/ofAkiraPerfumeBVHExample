//
//  SndTrack.h
//
//  Created by Akira Hayasaka on 3/27/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef StreamMaxim_Track_h
#define StreamMaxim_Track_h

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxOnsetDetection.h"

class SoundTrack
{
public:
    void setup(string audioSource, float p_normalSpeed, 
               int p_fftSize = 1024, int sampleRate = 44100)
    {
        fftSize = p_fftSize;
        sample = 0.0;
        position = 0;
        normalSpeed = p_normalSpeed;
        fft.setup(fftSize, 512, 256);
        oct.setup(sampleRate, fftSize, 10);        
        src.load(ofToDataPath(audioSource));
        srcName = audioSource;
        flatness = 0;
        
        bOnset = false;
        onsetD.setup(OFX_ODS_ODF_MKL);
    }
    
    void update(float speed)
    {
        int incr = round(speed / normalSpeed);
        position += incr;
        if (position >= src.length) 
        {
            position = 0;
        }
     
        sample = src.play(speed);
        if (fft.process(sample)) 
        {
            magnitudes = fft.magnitudes;
            magnitudesDB = fft.magnitudesDB;
            phases = fft.phases;
            avgPower = fft.avgPower;
            flatness = fft.spectralFlatness();
            
            bOnset = onsetD.isOnsetting(phases);
            
            oct.calculate(magnitudes);
            
            avgs.clear();
            peaks.clear();
            for (int i = 0; i < oct.nAverages; i++)
            {
                avgs.push_back(oct.averages[i]);
                peaks.push_back(oct.peaks[i]);
            }            
        }
    }
    
    float getPosition()
    {
        return ofMap(position, 0, src.length, 0.0, 1.0, true);
    }
    
    void updateWithFPS()
    {
        if (flatness > 0.06)
        {
            bool boo = true;
            ofNotifyEvent(flatEvent, boo, this);                
        }
        if (bOnset)
            ofNotifyEvent(onsetEvent, bOnset, this);        
    }
        
    void debugDraw()
    {        
        ofEnableAlphaBlending();
        
        ofPushStyle();
        ofDrawBitmapString(srcName, 32, 60);
        ofDrawBitmapString("length = " + ofToString(src.length), 32, 85);
        ofDrawBitmapString("flatness = " + ofToString(flatness), 32, 100);
        ofDrawBitmapString("position = " + ofToString(position), 32, 115);
        ofDrawBitmapString("position float = " + ofToString(getPosition()), 32, 130);        
        ofPopStyle();
        
        ofNoFill();
        ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 150, 0);
        

        if (getFlatness() > 0.0)
        {
            ofPushStyle();
            ofFill();                    
            ofSetColor(ofColor::green.r, ofColor::green.g, ofColor::green.b, 120);
            ofRect(0, 0, 900, 400);        
            ofNoFill();
            ofPopStyle();            
        }
        
		ofSetColor(225);
		ofDrawBitmapString("Average", 4, 18);
		
		ofSetLineWidth(1);	
        
		ofRect(0, 0, 900, 200);
        
		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
        
        ofBeginShape();
        for (int i = 0; i < avgs.size(); i++)
        {
            float x =  ofMap(i, 0, avgs.size(), 0, 900, true);
            ofVertex(x, 100 -avgs[i]*5.0f);
        }
        ofEndShape(false);
        
        for (int i = 0; i < avgs.size(); i += 10)
        {
            float x =  ofMap(i, 0, avgs.size(), 0, 900, true);
            ofDrawBitmapString(ofToString(i), x, 0);
        }
        
		ofPopMatrix();
        ofPopStyle();
        
        
        ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 350, 0);
        
		ofSetColor(225);
		ofDrawBitmapString("Peak", 4, 18);
		
		ofSetLineWidth(1);	
		ofRect(0, 0, 900, 200);
        
		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);
        
        ofBeginShape();
        for (int i = 0; i < peaks.size(); i++)
        {
            float x =  ofMap(i, 0, peaks.size(), 0, 900, true);
            ofVertex(x, 100 -peaks[i]*5.0f);
        }
        ofEndShape(false);
        
		ofPopMatrix();
        ofPopStyle();        
    
    }
    
    double          getSample() { return sample; }
    vector<float>   getAvgs() { return avgs; }
    vector<float>   getPeaks() { return peaks; }
    float *         getMagnitudes() { return magnitudes; }
    float *         getMagnitudesDB() { return magnitudesDB; }
    float *         getPhases() { return phases; }
    float *         getAvgPower() { return avgPower; }
    float           getFlatness() { return flatness; }
    bool            isOnset() { return bOnset; }
    ofEvent<bool>   onsetEvent;
    ofEvent<bool>   flatEvent;
    
private:
    ofxMaxiSample               src;
    ofxMaxiFFT                  fft;
    ofxMaxiFFTOctaveAnalyzer    oct;
    
    double          sample;
    long            position;
    float           normalSpeed;    
    vector<float>   avgs;
    vector<float>   peaks;
    float           flatness;
    
    int             fftSize;
    float *         magnitudes;
    float *         magnitudesDB;
    float *         phases;
    float *         avgPower;
    
    string          srcName;
    
    ofxOnsetDetection onsetD;
    bool            bOnset;
    
};

#endif
