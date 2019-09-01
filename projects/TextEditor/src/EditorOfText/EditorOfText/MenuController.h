/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#ifndef MENU_CONTROLLER
#define MENU_CONTROLLER

/* Defines the fraction of the
   window a single memory item takes.
   number is the inverse. */
#define MENU_ITEM_RATIO 10

/* Number of characters to offset the menu from the right of the screen. */
#define XOFFSET 1

#include <string>
#include "curses.h"
#include "customcolors.h"

using std::string;

/*******************************************************************************
 * Class Name:   MenuController
 * Purpose:      Controls the Text Editors Menu System
 *******************************************************************************/
class MenuController {
public:

	/*******************************************************************************
	 * Constructor
	 * Parameters:
	 *******************************************************************************/
	MenuController();

	/*******************************************************************************
	 * drawMenu(int, int)
	 * Parameters: int numCols, int numRows 
	 * Purpose: Draws the Text Editors Menu.
	 *******************************************************************************/
	void drawMenu(int, int);

private:
};

#endif