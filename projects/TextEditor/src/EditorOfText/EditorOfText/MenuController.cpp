/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	August 30th, 2019
*********************************************************************************/
#include "MenuController.h"

//Used to keep track of menu windows and menu panels
WINDOW* menuWindows[MENU_NUM_ITEMS];		/* A Menu Window */
PANEL* menuPanels[MENU_NUM_ITEMS];			/* A Menu Panel  */

/*
	Default instructor doesn't need to do anything.
*/
MenuController::MenuController() {
	
}

/*
	Initializes all the menu windows and panels
*/
MenuController::MenuController(WINDOW* mainWindow, int numRows, int numCols) {
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
			mvaddstr(0, ((numCols / MENU_ITEM_RATIO) * i) + XOFFSET, menuItems[i].c_str());
		}
		attroff(COLOR_PAIR(COLOR_MENU_PAIR)); //Unset the color

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
