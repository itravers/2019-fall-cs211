/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#include "MenuController.h"

// Constructor
MenuController::MenuController() {
	
}

// Draw the Menu
void MenuController::drawMenu(int numRows , int numCols) {
		//int xoffset = 1; 
		string menuItems[5] = { "File", "Edit", "View", "Tools", "Help" };
		//loop through and print menu items
		attron(COLOR_PAIR(COLOR_TITLE_PAIR));
		for (int i = 0; i <= menuItems->length(); i++) {
			mvaddstr(0, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET, menuItems[i].c_str());
		}
		attroff(COLOR_PAIR(COLOR_TITLE_PAIR));
}