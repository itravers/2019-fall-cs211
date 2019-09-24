#include "DialogBox.h"

//Constructor
DialogBox::DialogBox(WINDOW* parentWindow, string message, int yPos, int xPos, int nRows, int nCols) {

	//save the input values
	this->message = message;
	this->yPos = yPos;
	this->xPos = xPos;
	this->numRows = nRows;
	this->numCols = nCols;

	is_showing = false;

	//create a new window with those values
	window = subwin(parentWindow, numRows, numCols, yPos, xPos);
	panel = new_panel(window);
	hide_panel(panel);
}

//draw the dialog box
void DialogBox::draw() {
	if (is_showing) {
		//draw here

		wrefresh(window);
	}
}

//make the dialog box show itself
void DialogBox::show() {
	is_showing = true;
	show_panel(panel);
}

//check if the dialog box is showing
bool DialogBox::isShowing() {
	return is_showing;
}

void DialogBox::hide() {
	is_showing = false;
	hide_panel(panel);
}

