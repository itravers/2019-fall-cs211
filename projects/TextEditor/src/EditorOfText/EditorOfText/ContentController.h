/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 7th, 2019
*********************************************************************************/
#ifndef CONTENT_CONTROLLER
#define CONTENT_CONTROLLER

#include "curses.h"
#include "customcolors.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::to_string;

struct Location {
	int x;
	int y;
};


/*******************************************************************************
 * Class Name:   ContentController
 * Purpose:      The ContentController is responsible for controlling
				 the main displays displays contents. This doesn't include
				 the menu's or the status bar, or the borders, but just the
				 files we want to display
 *******************************************************************************/
class ContentController {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	ContentController();
	ContentController(WINDOW* mainWindow, int numRows, int numCols);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/
	
	 /*******************************************************************************
	  * Public Methods
	  *******************************************************************************/
	void displayContents(vector<string> lines);
	void displayContentsFromLine(vector<string> lines, int startLine);
	bool isContentMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string));
	void processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string));
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();

private:
	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/
	WINDOW* contentWindow;
	Location cursorLocation;
	vector<string>currentLines;
	int startLine = 0;
	int numCols;
	int numRows;

	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
	void displayCursor();
	void breakLongLines(vector<string>*lines);
	int numTabsInString(string s);
};

#endif