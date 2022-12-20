#ifndef _VideoFile
#define _VideoFile
#include "ofMain.h"

// ONLY DECLARATION

class VideoFile
{
public:
	VideoFile();
	vector<float> loopPoints;

	VideoFile(string _videoPath)
	{
		videoPath = _videoPath;
		isValidVideo = checkVideoFile(_videoPath);
	};

	string videoPath;
	bool isValidVideo = false;
	bool checkVideoFile(string v);
	float getSingleLoopPoint(int pos);
	vector<float> getallLoopPoints();
	void setSingleLoopPoints(int pos, float time);
	void setAllLoopPoints(vector<float> points);
	string getVideoname();

	void DefaultLoopPoints();

private:
	string videoName;
};

#endif