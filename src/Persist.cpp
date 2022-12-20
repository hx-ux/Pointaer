#include "Persist.h"
#include "VideoFile.h"

//CSV STRUCTURE
//pos 0 = videoFile
//pos 1,2,3 .. = loopPoints

void Persist::saveCSV()
{
	ofxCsvRow row;
	ofxCsv csv;

	ofFileDialogResult result = ofSystemSaveDialog("default.jpg", "Save");
	if (result.bSuccess) {
		string path = result.getPath();

		/*row.setString(0, currFile.videoPath);
		row.setFloat(1, currFile.getSingleLoopPoint(0));
		row.setFloat(2, currFile.getSingleLoopPoint(1));
		row.setFloat(3, currFile.getSingleLoopPoint(2));
		row.setFloat(4, currFile.getSingleLoopPoint(3));
		csv.addRow(row);*/

		string filepatj = path;
		csv.createFile(filepatj);
		csv.save(filepatj);
	}
	else
	{
			
	}

}


