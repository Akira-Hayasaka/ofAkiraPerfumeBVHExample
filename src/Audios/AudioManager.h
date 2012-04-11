//
//  AudioManager.h
//  StreamMaxim
//
//  Created by Akira Hayasaka on 3/28/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef StreamMaxim_AudioManager_h
#define StreamMaxim_AudioManager_h

#include "ofMain.h"
#include "ofxMaxim.h"
#include "SoundTrack.h"

const static int sampleRate = 44100;
const static int initialBufferSize = 2048;
const static float normalSpeed = 0.5;

class AudioManager : public ofBaseSoundInput, public ofBaseSoundOutput
{
public:
    void setup(const vector<string> trackFiles, const bool p_bMakeSound = true, const float p_speed = 1.0)
    {
        soundTracks.reserve(trackFiles.size() + 1);
        for (int i = 0; i < trackFiles.size(); i++)
        {
            SoundTrack* track = new SoundTrack();
            track->setup(trackFiles.at(i), normalSpeed);
            soundTracks.push_back(track);
        }
        
        soundStream.setup(2,0, sampleRate, initialBufferSize, 4);
        soundStream.setOutput(this); 
        soundStream.setInput(this);
        speed = p_speed;      
        bMakeSound = p_bMakeSound;
        
        whichTrackToDebug = 0;
    }
    
    void update()
    {
        for (int i = 0; i < soundTracks.size(); i++)
        {
            soundTracks.at(i)->updateWithFPS();
        }
    }
    
    void setSpeed(const float p_speed = 1.0)
    {
        speed = p_speed;
    }
    
    float getPosition()
    {
        return soundTracks.at(0)->getPosition();
    }
    
	void audioOut(float * output, int bufferSize, int nChannels)
    {
		for (int i = 0; i < bufferSize; i++)
        {            
            double sample = 0.0;
            for (int j = 0; j < soundTracks.size(); j++)
            {
                soundTracks.at(j)->update(handleSpeed());
                sample += soundTracks.at(j)->getSample();
            }
            
			mix.stereo(sample, outputs, 0.5);
            if (bMakeSound)
            {
                output[i * nChannels    ] = outputs[0]; 
                output[i * nChannels + 1] = outputs[1];
            }
		}        
    }
    
	void audioIn(float * input, int bufferSize, int nChannels)
    {
        for (int i = 0; i < bufferSize; i++) {}
    }
    
    void debugDraw(int whichTrack = 0)
    {
        soundTracks.at(whichTrack)->debugDraw();
    }
    
    vector<SoundTrack*> getSoundTracks()
    {
        return soundTracks;
    }

private:  
    ofSoundStream       soundStream;
	ofxMaxiMix          mix;    
    vector<SoundTrack*> soundTracks;        
    double              outputs[2];  
    float               speed;
    bool                bMakeSound;
    
    int                 whichTrackToDebug;
    
    float handleSpeed()
    {
        return speed * normalSpeed;
    }
};

#endif
