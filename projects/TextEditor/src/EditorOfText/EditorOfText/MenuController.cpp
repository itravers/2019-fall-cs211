/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#include "MenuController.h"

//Used to keep track of menu windows and menu panels
WINDOW* mainMenuWindow;
WINDOW* menuWindows[MENU_NUM_ITEMS];		/* A Menu Window */
PANEL* menuPanels[MENU_NUM_ITEMS];			/* A Menu Panel  */

/*
	Default constructor doesn't need to do anything.
*/
MenuController::MenuController() {
	
}

/*
	Initializes all the menu windows and panels
*/
MenuController::MenuController(WINDOW* mainWindow, int numRows, int numCols) {
	//setup the main menu
	mainMenuWindow = subwin(mainWindow, 0, 0, 0, 0);

	//set the color box for the main menu
	colorbox(mainMenuWindow, COLOR_MENU_PAIR, 0);

	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		
		WINDOW* newWin = nullptr;
		newWin = newwin(menuHeight, menuWidth, 2, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET);
		menuWindows[i] = newWin;

		//set a color box around each menuWindow
		colorbox(menuWindows[i], COLOR_MENU_PAIR, 1);

		//Set up the panels for the menu
		menuPanels[i] = new_panel(menuWindows[i]);

		//Setup the labels for each menu
		mvwaddstr(menuWindows[i], 0, XOFFSET, menuItems[i].c_str());

		//start the menus in hidden configuration
		hide_panel(menuPanels[i]);
	}

	
}

/*
	Draws the menu items.
*/
void MenuController::drawMenu(int numRows , int numCols) {
		//loop through and print main menu items
		attron(COLOR_PAIR(COLOR_MENU_PAIR));	//Set The Color For characters we are printing with.
		for (int i = 0; i <= menuItems->length(); i++) {
			mvwaddstr(mainMenuWindow, 0, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET, menuItems[i].c_str());
		}
		attroff(COLOR_PAIR(COLOR_MENU_PAIR)); //Unset the color

		//refresh the mainMenuWindow
		wrefresh(mainMenuWindow);

		//refresh all the menuWindows
		for (int i = 0; i < MENU_NUM_ITEMS; i++) {
			wrefresh(menuWindows[i]);
		}

		//update all the panels stacks
		update_panels();

		//draw the screen
		doupdate();
}

/*
	Closes all the menus
*/
void MenuController::closeAll() {
	//loop through and close all the menu windows
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		hide_panel(menuPanels[i]);
		wrefresh(menuWindows[i]);
	}

	update_panels();
	doupdate();
}

/*
	Hides a specific menu
*/
void MenuController::closeMenu(int menuNum) {
	hide_panel(menuPanels[menuNum]);
	wrefresh(menuWindows[menuNum]);
	update_panels();
}

/*
	Causes a given menu to pop up
*/
void MenuController::popupMenu(int menuNum) {
	//hide all panels
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		hide_panel(menuPanels[i]);
		update_panels();
	}

	show_panel(menuPanels[menuNum]);
	wrefresh(menuWindows[menuNum]);
}

/*
	This function was not written by me. I adapted it from the colorbox function in tui.c
	that the teacher supplied.
*/
void MenuController::colorbox(WINDOW* win, chtype color, int hasbox)
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
void MenuController::setcolor(WINDOW* win, chtype color)
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

/*
	Returns the current state of the menu enum to the caller
*/
MENU_STATE MenuController::getMenuState(){
	return MENU_STATE();
}

/*
	Called publically to set the state of the menu
*/
void MenuController::setMenuState(MENU_STATE state){
	menuState = state;
	switch (state) {
		case MENU_CLOSED: 
			closeAll();
			break;
		case MENU_FILE_OPEN:
			popupMenu(MENU_FILE);
			break;
		case MENU_EDIT_OPEN:
			popupMenu(MENU_EDIT);
			break;
		case MENU_VIEW_OPEN:
			popupMenu(MENU_VIEW);
			break;
		case MENU_TOOLS_OPEN:
			popupMenu(MENU_TOOLS);
			break;
		case MENU_HELP_OPEN:
			popupMenu(MENU_HELP);
			break;
	}
}

/*
	Called to check if a mouse click involves the menu
*/
bool MenuController::isMenuMouseEvent(MEVENT* mouseEvent, int numRows, 
									  int numCols, void(*changeStatus)(string)) {
	//check if the mouse event is clicking on a menu item
	//first we check and see if we have clicked in the menu bar at the top of the screen
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	//the menu is only on the top row, not counting the first or the last item
	if (x > 0 && x < numCols - 1 && y == 0) {
		return true;
	}else {
		return false;
	}

}

/*
	Called when the mouse has clicked on the menu.
	processes the mouse click by making the menu respond accordingly
*/
void MenuController::processMouseEvent(MEVENT* mouseEvent, int numRows, 
									   int numCols, void(*changeStatus)(string)) {
	//get the event coordinates
	int x = mouseEvent->x;
	int y = mouseEvent->y;

	//we have had a menu click, now we check if a specific item is being clicked
	for (int i = 0; i < MENU_NUM_ITEMS; i++) {
		string name = menuItems[i];
		int startX = ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET;
		int endX = ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET + name.length();
		if (x >= startX && x < endX) {
			switch (i) {
				case 0:
					setMenuState(MENU_FILE_OPEN);
					break;
				case 1:
					setMenuState(MENU_EDIT_OPEN);
					break;
				case 2:
					setMenuState(MENU_VIEW_OPEN);
					break;
				case 3:
					setMenuState(MENU_TOOLS_OPEN);
					break;
				case 4:
					setMenuState(MENU_HELP_OPEN);
					break;
			}
			break;
		}
		else {
			setMenuState(MENU_CLOSED);
		}
	}
}
