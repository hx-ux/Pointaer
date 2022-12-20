/*
 ofApp.cpp
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

 //#include "VideoFile.h"
 //#include "VideoFile.cpp"
#include "ofApp.h"
#include "Persist.h"

//

// SCROLL slider
#define BarInset 20
#define BarHeight 40


std::vector <VideoFile> videoList;
VideoFile defaultVideo = VideoFile("C:\\Users\\Jakob\\Videos\\hap.mov");

int currVideoStackPos = 0;

//--------------------------------------------------------------
void ofApp::setup()
{
	defaultVideo.isValidVideo = true;
	videoList.push_back(defaultVideo);
	

	barColor = ofColor::red;

	// generate default loopPoints
	videoList[currentLoopPoint].DefaultLoopPoints();

	// Limit drawing to the monitors rate
	ofSetVerticalSync(true);
	ofBackground(0);

	// load video
	player.load(videoList[currVideoStackPos].videoPath);
	player.setPixelFormat(ofPixelFormat::OF_PIXELS_GRAY);
	player.play();
	player.setVolume(0);
	player.setSpeed(1.0);
	player.setLoopState(OF_LOOP_NORMAL);
	inScrub = false;

	// Setup Ableton Link
	abletonLinkInstance.setup(120);
}

//--------------------------------------------------------------
void ofApp::update()
{
	abeltonLinkOldBeat = abletonLinkNewBeat;
	abletonLinkStatus = abletonLinkInstance.update();

	abletonLinkNewBeat = (int)floor(abletonLinkStatus.beat) % 4;
	if (abletonLinkActive)
	{
		if (abletonLinkNewBeat != abeltonLinkOldBeat)
		{
			setKeyFrame(videoList[currVideoStackPos].getallLoopPoints(), abletonLinkNewBeat);
			abeltonLinkOldBeat = abletonLinkNewBeat;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{

	if (videoList[currVideoStackPos].isValidVideo)
	{

		if (player.isLoaded())
		{
			// Draw the video
			ofSetColor(255, 255, 255);
			ofRectangle videoRect(0, 0, player.getWidth(), player.getHeight());
			videoRect.scaleTo(ofGetWindowRect());
			player.draw(videoRect.x, videoRect.y, videoRect.width, videoRect.height);

			if (drawGui)
			{
				drawTimeLine();
				drawEditModeInfo();
				drawLoopPoint(currentLoopPoint);

				// TODO single line
				if (abletonLinkActive)
				{
					drawAbletonLinkBeatBar();
				}
			}

			if (player.getError().length())
			{
				ofDrawBitmapStringHighlight(player.getError(), 20, 20);
			}
		}
		else
		{
			ofDrawBitmapStringHighlight("Movie is loading..." + videoList[currVideoStackPos].getVideoname(), 20, 20);
		}
	}
	else
	{
		ofDrawBitmapStringHighlight("MOVIE ERROR",20,20);
	}
}

void ofApp::load(std::string movie)
{
	ofSetWindowTitle(ofFilePath::getBaseName(movie));
	player.load(movie);
	player.play();
	lastMovement = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ')
	{
		player.setPaused(!player.isPaused());
	}

	else if (key == 'f')
	{
		isFullScreen = !isFullScreen;
		ofSetFullscreen(isFullScreen);
	}

	else if (key == OF_KEY_LEFT)
	{
		double seekFactor = 0.001;
		double position = player.getPosition() - seekFactor;
		player.setPosition(position);
	}

	else if (key == OF_KEY_RIGHT)
	{
		double seekFactor = 0.001;
		double position = player.getPosition() + seekFactor;
		player.setPosition(position);
	}

	else if (key == OF_KEY_DOWN)
	{
	}

	else if (key == OF_KEY_UP)
	{
		
	}
	else if (key == OF_KEY_DOWN)
	{
	
	}

	else if (key == 'p')
	{
		drawGui = !drawGui;
	}

	else if (key == '1')
	{
		setTimeLineLoopPoint(0);
	}

	else if (key == '2')
	{
		setTimeLineLoopPoint(1);
	}

	else if (key == '3')
	{
		setTimeLineLoopPoint(2);
	}

	else if (key == '4')
	{
		setTimeLineLoopPoint(3);
	}

	else if (key == 'b')
	{
		// toogle ableton link
		abletonLinkActive = !abletonLinkActive;
	}

	else if (key == 's')
	{
		// save / replace current loop point
		videoList[currVideoStackPos].setSingleLoopPoints(currentLoopPoint, player.getPosition());
		ofLog(OF_LOG_NOTICE, "set new keyframe at %1 " , player.getPosition());
	}

	else if (key == 'c')
	{
		
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (ofGetWindowRect().inside(x, y))
	{
		lastMovement = ofGetSystemTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (inScrub)
	{
		float position = static_cast<float>(x - BarInset) / getBarRectangleFull().width;
		position = std::max(0.0f, std::min(position, 1.0f));
		player.setPosition(position);
		lastMovement = ofGetSystemTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	ofRectangle bar = getBarRectangleFull();
	if (bar.inside(x, y))
	{
		inScrub = true;
		wasPaused = player.isPaused() || player.getIsMovieDone();
		player.setPaused(true);
		mouseDragged(x, y, button);
	}
	lastMovement = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if (inScrub)
	{
		inScrub = false;
		player.setPaused(wasPaused);
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}



void ofApp::drawAbletonLinkBeatBar()
{
	int quantum = (int)ceil(abletonLinkInstance.quantum());
	int nbeat;
	float dw;
	if (quantum < 1)
	{
		dw = (float)ofGetWidth();
		nbeat = 0;
	}
	else
	{
		dw = (float)ofGetWidth() / (float)quantum;
		nbeat = (int)floor(abletonLinkStatus.beat) % quantum;
	}
	// draws the 4 beats bar
	for (int i = 0; i < quantum; i++)
	{
		ofFill();
		ofSetColor((i <= nbeat) ? 255 : 128);
		ofDrawRectangle(i * dw, 400, dw, 50);
		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(i * dw, 400, dw, 50);
	}
}

void ofApp::setKeyFrame(vector<float> frames, int pos)
{
	if (frames[pos])
	{
		currentLoopPoint = pos;
		player.setPosition(frames[pos]);
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	
}

ofRectangle ofApp::getBarRectangleFull() const
{
	return ofRectangle(BarInset, ofGetWindowHeight() - BarInset - BarHeight, ofGetWindowWidth() - (2 * BarInset), BarHeight);
}

ofRectangle ofApp::getBarRectanglePoint() const
{
	return ofRectangle(ofGetWindowHeight() - BarInset - BarHeight - 20, ofGetWindowHeight() - BarInset - BarHeight + 50, 20, BarHeight);
}

void ofApp::drawLoopPoint(int curFrame)
{
	int pWidth = 5;
	int pHeight = BarHeight;
	int pX = ofGetWindowWidth() - (2 * BarInset);
	int pY = ofGetWindowHeight() - BarInset - BarHeight;
	int alpha = 255;

	int counter = 1;

	for (int i = 0; i < videoList[currVideoStackPos].getallLoopPoints().size(); i++)
	{
		ofFill();
		counter == currentLoopPoint + 1 ? ofSetColor(ofColor::wheat) : ofSetColor(ofColor::yellow);

		ofDrawBitmapString(ofToString(counter), (pX * videoList[currVideoStackPos].getallLoopPoints()[i]) + pWidth * 4, pY - 5);
		ofDrawRectangle((pX * videoList[currVideoStackPos].getallLoopPoints()[i]) + pWidth * 4, pY, pWidth, pHeight);
		counter++;
	}
}

void ofApp::drawEditModeInfo()
{
	ofSetColor(ofColor::black);
	ofDrawRectangle(0, 0, 300, 100);
	ofSetColor(ofColor::white);
	string mode = (abletonLinkActive) ? "ABLETON SYNC " : "EDIT MODE";
	ofDrawBitmapString(mode, 20, 40);
	ofDrawBitmapString("Current POINT " + ofToString(currentLoopPoint + 1), 20, 60);
	ofDrawBitmapString("Time Postiton of point  " + ofToString(videoList[currVideoStackPos].getSingleLoopPoint(currentLoopPoint)), 20, 80);
	ofDrawBitmapString("Video name  " + videoList[currVideoStackPos].getVideoname(), 20, 90);
	// TODO Get fps

	// ableton stuff
	ofSetColor(ofColor::black);
	ofDrawRectangle(350, 0, 300, 100);
	ofSetColor(ofColor::white);
	(abletonLinkInstance.numPeers() == 0) ? ofSetColor(ofColor::red) : ofSetColor(ofColor::green);
	// TODO get number of peers
	ofDrawBitmapString("Number of peers: " + ofToString(abletonLinkInstance.numPeers()), 400, 30);
	(!abletonLinkActive) ? ofSetColor(ofColor::red) : ofSetColor(ofColor::green);
	string active = (abletonLinkActive) ? "yes" : "no";
	ofDrawBitmapString("Ableton link activated ? " + active, 400, 50);
	ofDrawBitmapString("Tempo " + ofToString(abletonLinkInstance.tempo()), 400, 70);
	ofDrawBitmapString("Press B to toggle " + active, 400, 90);
	ofSetColor(ofColor::white);
}

void ofApp::abletonLinkSetup()
{
	abletonLinkInstance.setup(120);
	ofSetBackgroundColor(0, 0, 0);
	ofSetVerticalSync(true);
}

void ofApp::drawTimeLine()
{
	// draws the timelime
	// outer Rect
	ofNoFill();
	ofRectangle bar = getBarRectangleFull();
	ofSetColor(barColor, 255);
	ofDrawRectangle(bar);
	// inner rect for current Pos
	ofFill();
	ofSetColor(barColor, 200);
	bar.width *= player.getPosition();
	// cout << ofToString(player.getPosition());
	ofDrawRectangle(bar);
}

void ofApp::setTimeLineLoopPoint(int position)
{
	currentLoopPoint = position;
	player.setPosition(videoList[currVideoStackPos].getSingleLoopPoint(position));
}