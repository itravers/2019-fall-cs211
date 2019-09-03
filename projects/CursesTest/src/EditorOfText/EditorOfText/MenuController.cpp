/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#include "MenuController.h"

// Constructor
MenuController::MenuController() {
	//menuWindow = new WINDOW;
	popupMenu(10, 12);
}

// Draw the Menu
void MenuController::drawMenu(int numRows , int numCols) {
		//loop through and print menu items
		attron(COLOR_PAIR(COLOR_TITLE_PAIR));	//Set The Color For characters we are printing with.
		for (int i = 0; i <= menuItems->length(); i++) {
			mvaddstr(0, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET, menuItems[i].c_str());
		}
		attroff(COLOR_PAIR(COLOR_TITLE_PAIR)); //Unset the color
}

void MenuController::popupMenu(int numRows, int numCols) {
	//menuWindow = new WINDOW;
	//WINDOW* menuWindow;
	//menuWindow = newwin(numRows, numCols, 1, 1); //create a new menuWindow
	//box(menuWindow, 0, 0);
}