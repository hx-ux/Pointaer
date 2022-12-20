#ifndef _Persist // if this class hasn't been defined, the program can define it
#define _Persist // by using this if statement you prevent the class to be called more than once which would confuse the compiler
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework
#include "ofxCsv.h"
#include "VideoFile.h"


// NOT YET IMPELMENTED !!!

class Persist {
public:
	Persist();
	void setup();
	void saveCSV();

private:

	//to csv
	string loopPointsToString();

	//from CSV
	vector<double> loopPointsToVector(string fromString);
};

#endif