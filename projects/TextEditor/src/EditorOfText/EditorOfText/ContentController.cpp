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
	cursorLocation.x = 0;
	cursorLocation.y = 0;
	contentWindow = subwin(mainWindow, numRows - 4, numCols - 2, 2, 1);
}

/*
	Displays the contents of a lines vector to the content window
*/
void ContentController::displayContents(vector<string> lines) {
	/* Save Current lines*/
	werase(contentWindow);
	currentLines = lines;

	int firstLine = 0;
	int margin = 0;
	
	//for (int i = 0; i < lines.size(); i++) {
	//	mvwaddstr(contentWindow, firstLine + i, margin, lines[i].c_str());
	//}
	//int startLine = 0;
	displayContentsFromLine(lines, startLine);
	displayCursor();
}

/*
	Displays the contents of the lines vector to the content window
	starting at line startLine
*/
void ContentController::displayContentsFromLine(vector<string> lines, int startLine) {
	//currentLines = lines;
	werase(contentWindow);
	int firstLine = 0, margin = 0;
	int n = 0;
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
void ContentController::moveCursorDown(int numRows) {
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