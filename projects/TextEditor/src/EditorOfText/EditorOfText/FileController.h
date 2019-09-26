/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 6th, 2019
*********************************************************************************/
#ifndef FILE_CONTROLLER
#define FILE_CONTROLLER

#include "TextEditor.h"
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::endl;

enum READ_WRITE { READ, WRITE };

/*******************************************************************************
 * Class Name:   FileController
 * Purpose:      The FileController will be responsible for all possible
 *				 reading and loading of a file into memory. It will also
 *				 be responsible for writing memory back to the file itself.
 *******************************************************************************/
class TextEditor; //forward declare TextEditor
class FileController {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	FileController(TextEditor* t);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/

	/*******************************************************************************
	 * Public Methods
	 *******************************************************************************/
	bool readFile(string fileName, vector<string>& lines, READ_WRITE readOrWrite);		/* Open A File & read into vector*/
	bool writeFile(string fileName, vector<string>& lines);
	bool closeFile(ifstream);					/* Closes an Input File. */
	bool closeFile(ofstream);					/* Closes an output file. */

private:
	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/
	ifstream inFile;
	ofstream outFile;

	/* Objects */
	TextEditor* textEditor;

	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
};

#endif