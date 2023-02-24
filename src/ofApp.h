/*
 testApp.h
 ofxHapPlayerExample

 Copyright (c) 2013, Tom Butterworth. All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxAbletonLink.h"
#include "ofxCsv.h"
#include "VideoFile.h"

class ofApp : public ofBaseApp {
public:
	//Standart Stuff
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void disableAudi0(); 


	void drawAbletonLinkBeatBar();
	void setKeyFrame(vector<float> frames, int pos);

	bool drawGui = true;
	bool isFullScreen = false;

	void load(std::string movie);
	ofRectangle getBarRectangleFull() const;
	ofRectangle getBarRectanglePoint() const;
	void drawLoopPoint(int curFrame);
	ofxHapPlayer player;
	uint64_t lastMovement;

	bool wasPaused;
	bool drawBar;
	bool inScrub;

	ofRectangle loopPointRec;

	void drawEditModeInfo();

	ofColor barColor;
	void setTimeLineLoopPoint(int mode);

	int currentLoopPoint = 0;

	void drawTimeLine();

	ofxAbletonLink abletonLinkInstance;
	void abletonLinkSetup();
	ofxAbletonLink::Status abletonLinkStatus;
	bool abletonLinkActive = false;
	int abletonLinkNewBeat;
	int abeltonLinkOldBeat;
};
