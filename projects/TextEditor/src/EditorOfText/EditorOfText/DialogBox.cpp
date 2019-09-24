#include "DialogBox.h"
#include "customcolors.h"

//Constructor
DialogBox::DialogBox() {}

DialogBox::DialogBox(WINDOW* parentWindow, string message, int yPos, int xPos, int nRows, int nCols) {
	this->parentWindow = parentWindow;

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

void DialogBox::displayDialogBox(string message, int yPos, int xPos, int nRows, int nCols) {
	
	//set the color box for the dialog box
	colorbox(window, COLOR_MENU_PAIR, 1);
	mvwaddstr(window, 1, 1, message.c_str());
	
	wrefresh(window);
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

//hides the dialog box
void DialogBox::hide() {
	is_showing = false;
	hide_panel(panel);
}

//returns the message the dialog box is displaying
string DialogBox::getMessage() {
	return message;
}

/*
	This function was not written by me. I adapted it from the colorbox function in tui.c
	that the teacher supplied.
*/
void DialogBox::colorbox(WINDOW* win, chtype color, int hasbox)
{
	int maxy;
#ifndef PDCURSES
	int maxx;
#endif
	chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

	setcolor(win, color);

#ifdef A_COLOR
	if (has_colors())
		wbkgd(win, COLOR_PAIR(color & A_CHARTEXT) | (attr & ~A_REVERSE));
	else
#endif
		wbkgd(win, attr);

	werase(win);

#ifdef PDCURSES
	maxy = getmaxy(win);
#else
	getmaxyx(win, maxy, maxx);
#endif
	if (hasbox && (maxy > 2))
		box(win, 0, 0);

	touchwin(win);
	wrefresh(win);
}

/*
	This function was not written by me. I adapted it from the setcolor
	function in tui.c, supplied by the teacher.
*/
void DialogBox::setcolor(WINDOW* win, chtype color)
{
	chtype attr = color & A_ATTR;  /* extract Bold, Reverse, Blink bits */

#ifdef A_COLOR
	attr &= ~A_REVERSE;  /* ignore reverse, use colors instead! */
	wattrset(win, COLOR_PAIR(color & A_CHARTEXT) | attr);
#else
	attr &= ~A_BOLD;     /* ignore bold, gives messy display on HP-UX */
	wattrset(win, attr);
#endif
}