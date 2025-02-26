/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 6th, 2019
*********************************************************************************/
#include "FileController.h"

/*
	Default Constructor
*/
FileController::FileController() {

}

/*
	Opens a file in the current working directory by name.
	Reads the file into a string vector, line by line.
*/
bool FileController::readFile(string fileName, vector<string>& lines, READ_WRITE readOrWrite, void(* changeStatus)(string)) {
	//check if we are reading or writing
	if (readOrWrite == READ) {
		changeStatus("Opening File: " + fileName);

		//Close the inFile if it is currently open
		if (inFile) inFile.close();

		//try to open the new file by name
		try {
			//open the input file
			inFile.open(fileName.c_str());

			//check if the file was properly opened
			if (!inFile) {
				throw string("Error: Couldn't Open File " + fileName + " for reading!");
			}

			//now we are going to loop through the text and read every line into the lines vector
			string line = "";
			while (getline(inFile, line)) {
				lines.push_back(line);
			}
			
			//it looks like we succeded, return true to caller
			return true;
		}
		catch (string error) {
			//print our error to the status bar
			changeStatus(error);
			return false;
		}

	}
	else if(readOrWrite == WRITE) {
		//we are writing
	}
}