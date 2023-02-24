#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}

// to deactivate the audio 

//
//void ofxHapPlayer::AudioOutput::start()
//{
//	// TODO fixed mute the audio
//	//if (!_started)
//	//{
//	//	ofSoundStreamSettings settings;
//	//	settings.numInputChannels = 0;
//	//	settings.numOutputChannels = _channels;
//	//	settings.sampleRate = _sampleRate;
//	//	settings.setOutListener(this);
//
//	//	// TODO: best values for last 2 params?
//	//	settings.bufferSize = 128;
//	//	settings.numBuffers = 2;
//
//	//	_started = _soundStream.setup(settings);
//	//	if (!_started)
//	//	{
//	//		ofLogError("ofxHapPlayer", "Error starting audio playback.");
//	//	}
//	//}
//	//else
//	//{
//	//	_soundStream.start();
//	//}
//}