/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 7th, 2019
*********************************************************************************/
#include "ContentController.h"

/*
	The default constructor
*/
ContentController::ContentController() {
	cursorLocation.x = 0;
	cursorLocation.y = 0;
}

ContentController::ContentController(WINDOW* mainWindow, int numRows, int numCols) {
	this->numCols = numCols - 3;
	this->numRows = numRows;
	cursorLocation.x = 0;
	cursorLocation.y = 0;
	contentWindow = subwin(mainWindow, numRows - 4, this->numCols, 2, 1);
}

/*
	Displays the contents of a lines vector to the content window
*/
void ContentController::displayContents(vector<string> lines) {
	displayContentsFromLine(lines, startLine);
	displayCursor();
}

/*
	Displays the contents of the lines vector to the content window
	starting at line startLine
*/
void ContentController::displayContentsFromLine(vector<string> lines, int startLine) {
	currentLines = lines;
	werase(contentWindow);
	int firstLine = 0, margin = 0;
	int n = 0;
	breakLongLines(&currentLines); //break longer lines up into multiple lines
	//int numWraps = 0; //track how many times we word wrap
	for (int i = startLine; i < currentLines.size(); i++) {
		mvwaddstr(contentWindow, firstLine + n, margin, currentLines[i].c_str());
		n++;
	}
	wrefresh(contentWindow);
	displayCursor();
}


/*
	Checks if this mouse event has anything to do with the content controller
*/
bool ContentController::isContentMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string)) {
	//check if the mouse is over the content pane
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	if (x > 0 && y > 1 && x < numCols - 1 && y < numRows - 2) {
		//changeStatus("Mouse Clicked: " + to_string(x) + " : " + to_string(y));
		return true;
	}
	else {
		return false;
	}
}


/*
	Called for a mouse event on the window
*/
void ContentController::processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols, void(*changeStatus)(string)) {
	changeStatus("mouseevent");
	//attron(A_BLINK);
	//wmove(contentWindow, 5, 5);
	wrefresh(contentWindow);
}

/*
	Display the cursor on the content window
*/
void ContentController::displayCursor() {
	attron(COLOR_PAIR(COLOR_CURSOR_PAIR));
	mvwaddstr(contentWindow, cursorLocation.y, cursorLocation.x, "C");
	attroff(COLOR_PAIR(COLOR_CURSOR_PAIR));
	wrefresh(contentWindow);
}

/*
	Moves the cursor up
*/
void ContentController::moveCursorUp() {
	int y = cursorLocation.y;
	if (y <= 0) {
		y = 0;
		if (startLine > 0) {
			displayContentsFromLine(currentLines, --startLine);
		}
	}
	else {
		y--;
	}
	cursorLocation.y = y;
	displayContents(currentLines);
}

/*
	Moves the cursor down
*/
void ContentController::moveCursorDown() {
	int y = cursorLocation.y;
	if (y >= numRows-5) {
		//make sure we wan't scroll down past the file
		if (startLine < currentLines.size()-1) {
			displayContentsFromLine(currentLines, ++startLine);
		}
	}
	else {
		y++;
		cursorLocation.y = y;
		displayContents(currentLines);
	}
	
}

/*
	Moves the cursor left
*/
void ContentController::moveCursorLeft() {

}

/*
	Moves the cursor right
*/
void ContentController::moveCursorRight() {

}

/*
	Breaks long lines in the lines vector up
	if the line is longer than numCols, the line
	is broken up and added to itself.
*/
void ContentController::breakLongLines(vector<string>*lines) {
	//scroll through until we find the first line that is too long
	for (int i = 0; i < lines->size(); i++) {
		string line = (*lines)[i];
		//strings with a \t have 4 bigger size for each \t present
		size_t numTabs = numTabsInString(line)*6;
		//size_t lineSize = line.size() + (4 * numTabs);
		if (line.size() > numCols) {
			//we found a line too long.
			int overLength = line.size() - numCols - numTabs;
			
			//break the line into two strings
			string overFlowString = line.substr(numCols - numTabs, overLength);
			string mainString = line.substr(0, numCols - numTabs);

			//change current line to mainString
			(*lines)[i] = mainString;

			//insert overFlowString after currentLine we just edited
			auto it = lines->begin() + i + 1;
			lines->insert(it, overFlowString);
			
			//we only wanted to find the first one
			break;
		}
		//if we haven't found any lines to long we'll return, this is the base case
		if(i == lines->size() - 1) return;
	}
	//now we will find the rest of them.
	breakLongLines(lines);
}

/*
	Gives us the count of how many \t tabs are in a string
*/

int ContentController::numTabsInString(string s) {
	//loop through string and count num '\t'
	int numTabs = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '\t')numTabs++;
	}
	return numTabs;
}