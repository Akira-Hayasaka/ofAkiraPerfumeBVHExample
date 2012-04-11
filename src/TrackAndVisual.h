//
//  TrackAndVisual.h
//  PerfumeAR
//
//  Created by Akira Hayasaka on 4/10/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef PerfumeAR_TrackAndVisual_h
#define PerfumeAR_TrackAndVisual_h

#include "SoundTrack.h"
#include "NoisyString.h"
#include "GrowingCircle.h"

class TrackAndVisual
{
public:
    void setup(vector<SoundTrack*> soundTracks)
    {
        tracks = soundTracks;
        ofAddListener(soundTracks.at(1)->flatEvent, this, &TrackAndVisual::genNoisySphere);
        ofAddListener(soundTracks.at(0)->flatEvent, this, &TrackAndVisual::genGrowingCircle);        
        nsOnset = false;
        gcOnset = false;
    }
    
    void update()
    {
        if (nsOnset)
        {
            NoisySphere ns;
            ns.setup();
            nss.push_back(ns);     
            nsOnset = false;
        }
        if (gcOnset)
        {
            GrowingCircle gc;
            gc.setup();
            gcs.push_back(gc);  
            gcOnset = false;
        }
        
        for (int i = 0; i < nss.size(); i++)
        {
            nss.at(i).update();
        }
        for (int i = 0; i < gcs.size(); i++)
        {
            gcs.at(i).update();
        }        
    }
    
    void draw()
    {
        for (int i = 0; i < nss.size(); i++)
        {
            nss.at(i).draw();
        }
        
        for (int i = 0; i < gcs.size(); i++)
        {
            gcs.at(i).draw(0,0);
        }        
    }
    
private:
    
    void genNoisySphere(bool& arg)
    {
        nsOnset = true;          
    }
    
    void genGrowingCircle(bool& arg)
    {
        gcOnset = true;
    }
    
    vector<SoundTrack*> tracks;
    vector<NoisySphere> nss;
    vector<GrowingCircle> gcs;  
    bool nsOnset;
    bool gcOnset;
    
};



#endif
