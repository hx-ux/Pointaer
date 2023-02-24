#include "Persist.h"
#include "VideoFile.h"

//CSV STRUCTURE
//pos 0 = videoFile
//pos 1,2,3 .. = loopPoints

void Persist::saveToCSV(VideoFile f)
{
	xml.clear();
	xml.save("mySettings.xml");
}

