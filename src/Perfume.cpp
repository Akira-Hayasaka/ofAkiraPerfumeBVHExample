//
//  Perfume.cpp
//  PerfumeAR
//
//  Created by Akira Hayasaka on 3/25/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#include "Perfume.h"

class Tracker
{
public:
	
	const ofxBvhJoint *joint;
	deque<ofVec3f> points;
	
	void setup(const ofxBvhJoint *o)
	{
		joint = o;
	}
	
	void update()
	{
		const ofVec3f &p = joint->getPosition();
		
		if (p.distance(points.front()) > 1)
			points.push_front(joint->getPosition());
		
		if (points.size() > 15)
			points.pop_back();
	}
	
	void draw()
	{
		if (points.empty()) return;
		
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < points.size() - 1; i++)
		{
			float a = ofMap(i, 0, points.size() - 1, 1, 0);
			
			ofVec3f &p0 = points[i];
			ofVec3f &p1 = points[i + 1];
			
			float d = p0.distance(p1);
			a *= ofMap(d, 1, 10, 0, 1);
			
			glColor4f(1, 1, 1, a);
			glVertex3fv(points[i].getPtr());
		}
		glEnd();
	}
};

vector<Tracker*> trackers;


void Perfume::setup()
{
	play_rate = play_rate_t = 1;
	
	// setup bvh
	bvh[0].load("bvh/dancingFiles/kashiyuka.bvh");
    bvh[1].load("bvh/dancingFiles/nocchi.bvh");
    bvh[2].load("bvh/dancingFiles/aachan.bvh");
	
	for (int i = 0; i < 3; i++)
	{
		bvh[i].play();
	}
	
	track.loadSound("main_audio/perhp.wav");
	track.play();
	track.setLoop(true);
	
	// setup tracker
	for (int i = 0; i < 3; i++)
	{
		ofxBvh &b = bvh[i];
		
		for (int n = 0; n < b.getNumJoints(); n++)
		{
			const ofxBvhJoint *o = &b.getJoint(n);
			Tracker *t = new Tracker;
			t->setup(o);
			trackers.push_back(t);
		}
	}  
    
    ofRegisterKeyEvents(this);
}

void Perfume::update()
{
	play_rate += (play_rate_t - play_rate) * 0.3;
	track.setSpeed(play_rate);
	
	float t = (track.getPosition() * 62.14);
	t = t / bvh[0].getDuration();
	
	for (int i = 0; i < 3; i++)
	{
		bvh[i].setPosition(t);
		bvh[i].update();
	}
	
	for (int i = 0; i < trackers.size(); i++)
	{
		trackers[i]->update();
	}
}

void Perfume::draw(ofxARToolkitPlus artk, TrackAndVisual tvis)
{
    glEnable(GL_DEPTH_TEST);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	artk.applyProjectionMatrix();
    int numDetected = artk.getNumDetectedMarkers();
    if (numDetected > 0)
    {
        artk.applyModelMatrix(0);
        ofPushMatrix();
        {
            ofRotate(90, -1, 0, 0);            
            ofScale(0.1, 0.1, 0.1);
            ofTranslate(100, -100);   
            
            tvis.draw();            
            
            ofScale(1, -1, 1);
            
            ofSetColor(ofColor::white);
            
            ofFill();
            
            // draw actor
            for (int i = 0; i < 3; i++)
            {
                //drawBVHMotion(bvh[i]);
                bvh[i].draw();                
            }
            
            // draw tracker
            glDisable(GL_DEPTH_TEST);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            
            ofSetColor(ofColor::white, 80);
            for (int i = 0; i < trackers.size(); i++)
            {
                trackers[i]->draw();
            }
        }
        ofPopMatrix();
    }
}

void Perfume::drawBVHMotion(ofxBvh bvh)
{
//    ofPushStyle();
//    ofFill();
//    
//    for (int i = 0; i < bvh.getNumJoints(); i++)
//    {
//        ofxBvhJoint o = bvh.getJoint(i);
//        glPushMatrix();
//        glMultMatrixf(o.getGlobalMatrix().getPtr());
//        
//        if (o.isSite())
//        {
//            ofSetColor(ofColor::yellow);
//            billboard();
//            ofCircle(0, 0, 6);
//        }
//        else if (o.getChildren().size() == 1)
//        {
//            ofSetColor(ofColor::white);		
//            billboard();
//            ofCircle(0, 0, 2);
//        }
//        else if (o.getChildren().size() > 1)
//        {
//            if (o.isRoot())
//                ofSetColor(ofColor::cyan);
//            else
//                ofSetColor(ofColor::green);
//            
//            billboard();
//            ofCircle(0, 0, 4);
//        }
//        
//        glPopMatrix();
//    }
//    
//    ofPopStyle();
}

void Perfume::keyPressed(ofKeyEventArgs& key)
{
	if(key.key == 'p') 
    {
		play_rate_t = -1;
    }
}

void Perfume::keyReleased(ofKeyEventArgs& key)
{
	if(key.key == 'p') 
    {
		play_rate_t = 1;
    }
}

void Perfume::billboard()
{
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	
	float inv_len;
	
	m[8] = -m[12];
	m[9] = -m[13];
	m[10] = -m[14];
	inv_len = 1. / sqrt(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]);
	m[8] *= inv_len;
	m[9] *= inv_len;
	m[10] *= inv_len;
	
	m[0] = -m[14];
	m[1] = 0.0;
	m[2] = m[12];
	inv_len = 1. / sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
	m[0] *= inv_len;
	m[1] *= inv_len;
	m[2] *= inv_len;
	
	m[4] = m[9] * m[2] - m[10] * m[1];
	m[5] = m[10] * m[0] - m[8] * m[2];
	m[6] = m[8] * m[1] - m[9] * m[0];
	
	glLoadMatrixf(m);
}
