#include "VideoFile.h"
#include "Csv.h"

bool VideoFile::checkVideoFile(string v)
{
	// TODO impelement

	return true;
}

float VideoFile::getSingleLoopPoint(int pos)
{
	return loopPoints[pos];
}

vector<float> VideoFile::getallLoopPoints()
{
	return loopPoints;
}

void VideoFile::setSingleLoopPoints(int pos, float time)
{
	ofLog(OF_LOG_NOTICE, "set loop point add %1",pos);
	loopPoints.at(pos) = time;
}

void VideoFile::setAllLoopPoints(vector<float> points)
{
	loopPoints = points;
}

string VideoFile::getVideoname()
{
	return ofFilePath::getBaseName(videoPath);
}

void VideoFile::DefaultLoopPoints()
{
	vector<float> nums;  // create default loop points
	nums.push_back(0.1);
	nums.push_back(0.2);
	nums.push_back(0.7);
	nums.push_back(0.9);
	loopPoints = nums;
}