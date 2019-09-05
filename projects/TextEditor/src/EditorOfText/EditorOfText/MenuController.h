/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#ifndef MENU_CONTROLLER
#define MENU_CONTROLLER
#define A_ATTR (A_ATTRIBUTES)

/* Defines the fraction of the
   window a single memory item takes.
   number is the inverse. */
#define MENU_ITEM_RATIO 10
#define MENU_NUM_ITEMS 5	/* Number of Menu Items */
#define MENU_HEIGHT 10		/* Menu Height */
#define MENU_WIDTH 20		/* Menu Width  */
#define MENU_FILE 0
#define MENU_EDIT 1
#define MENU_VIEW 2
#define MENU_TOOLS 3
#define MENU_HELP 4

/* Number of characters to offset the menu from the right of the screen. */
#define XOFFSET 1

#include <string>
#include <vector>
#include "curses.h"
#include "panel.h"
#include "customcolors.h"

using std::string;
using std::vector;

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
	MenuController(WINDOW*, int, int);

	/*******************************************************************************
	 * drawMenu(int, int)
	 * Parameters: int numCols, int numRows 
	 * Purpose: Draws the Text Editors Menu.
	 *******************************************************************************/
	void drawMenu(int, int);

	void popupMenu(int);
	void closeMenu(int);
	void closeAll();
	void colorbox(WINDOW* win, chtype color, int hasbox);
	void setcolor(WINDOW* win, chtype color);

private:
	/* A List of the items we will have in our menu. */
	string menuItems[MENU_NUM_ITEMS] = { "File", "Edit", "View", "Tools", "Help" };

	//WINDOW* menuWindows[MENU_NUM_ITEMS];		/* A Menu Window */
	//WINDOW** menuWindows;
	//vector<WINDOW*> menuWindows;
	

	/* The menu dimensions */
	const int menuHeight = MENU_HEIGHT;
	const int menuWidth = MENU_WIDTH;
};

#endif