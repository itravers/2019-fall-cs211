/**
	Isaac Travers
	CIS 211 - Data Structures
	August 30th, 2019
	Homework Assignment 1

	Get used to using the curses api.
	Get used to git & githubs issues and project tracking.
	Design the gui to a basic text editor.
	This was based on a template supplied by the teacher and expanded from there.
*/

/* Defines */
#define PDC_DLL_BUILD 1			//Used for Curses
#define A_ATTR (A_ATTRIBUTES)
#define ctrl(x) ((x) & 0x1f)	//CTRL-x masking

/* Includes */
#include "curses.h"
#include "panel.h"
#include "customcolors.h"
#include "MenuController.h"
#include <string>
#include <iostream>
#include <stdio.h>

/* Namespaces */
using std::string;
using std::cin;
using std::cout;

/* Function Prototypes*/
void initColor(void);			// Initialize the Color System
void drawBorder(int, int);		// Border around the screen
void drawStatus(int, int);		// Draws the status bar at the bottom of the screen
void drawScreen(int, int);		// Draws everything associated with the screen.
static void colorbox(WINDOW*, chtype, int);

/* Objects */
MenuController menuController;

static WINDOW* titleWindow;


/* Start of the Program. */
int main(void) {
	//Setup Window
	int numRows = 0;
	int numCols = 0;

	//Initialze Curses
	WINDOW* mainWindow = nullptr;
	
	//initialize screen to begin curses mode
	mainWindow = initscr();

	//set up all the color pairs
	initColor();

	//go near-full screen
	getmaxyx(mainWindow, numRows, numCols);
	resize_term(numRows - 1, numCols - 1);
	getmaxyx(mainWindow, numRows, numCols);

	//turn off key echo
	noecho();
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	curs_set(0);

	//Initialize Menu Controller
	MenuController::MenuController(mainWindow, numRows, numCols);

	//demo text
	mvaddstr(3 , 2, "Welcome to the Editor of Text. Where you can do wonderful things... like edit text.");
	mvaddstr(4 , 2, "Currently, you can't edit any text, sorry. However, you can manipulate the menus!");
	mvaddstr(6 , 2, "Menu Commands: ");
	mvaddstr(7 , 4, "CTRL-f - Popup File Menu ");
	mvaddstr(8 , 4, "CTRL-e - Popup Edit Menu ");
	mvaddstr(9 , 4, "CTRL-v - Popup View Menu ");
	mvaddstr(10, 4, "CTRL-t - Popup Tool Menu ");
	mvaddstr(11, 4, "CTRL-h - Popup Help Menu ");
	mvaddstr(12, 4, "CTRL-d - Close All Menus ");
	mvaddstr(13, 4, "CTRL-c - Close The Program! ");

	

	//Draw the screen
	drawScreen(numRows, numCols);

	menuController.setMenuState(MENU_VIEW_OPEN);
	
	//Get Keyboard input to control the menu's
	char c;
	while ((c = getch()) != KEY_END) {
		switch (c) {
			case ctrl('f'):
				//menuController.popupMenu(MENU_FILE);
				menuController.setMenuState(MENU_FILE_OPEN);
				break;
			case ctrl('e'):
				//menuController.popupMenu(MENU_EDIT);
				menuController.setMenuState(MENU_EDIT_OPEN);
				break;
			case ctrl('v'):
				//menuController.popupMenu(MENU_VIEW);
				menuController.setMenuState(MENU_VIEW_OPEN);
				break;
			case ctrl('t'):
				//menuController.popupMenu(MENU_TOOLS);
				menuController.setMenuState(MENU_TOOLS_OPEN);
				break;
			case ctrl('h'):
				//menuController.popupMenu(MENU_HELP);
				menuController.setMenuState(MENU_HELP_OPEN);

				break;
			case ctrl('d'):
				menuController.setMenuState(MENU_CLOSED);
				break;
			case ctrl('c'):
				nodelay(mainWindow, TRUE);
				keypad(mainWindow, TRUE);
				mvaddstr(0, 0, "Press ANYKEY to continue...");
				endwin();

				return 0;
				break;
		}
	}

	refresh(); //Tells Curses to Draw
	
	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	char pause;//
	cin >> pause;
	endwin();

	return 0;
}

/*
	Draws everything currently on the screen.
*/
void drawScreen(int numRows, int numCols) {
	drawBorder(numRows, numCols);
	menuController.drawMenu(numRows, numCols);
	drawStatus(numRows, numCols);
}

/*
	Draws a status to the bottom of the screen.
*/
void drawStatus(int numRows, int numCols) {
	int xoffset = 1;
	attron(COLOR_PAIR(COLOR_MAIN_PAIR));
	mvaddstr(numRows-1, xoffset, "STATUS: Everything IS Okay!");
	attroff(COLOR_PAIR(COLOR_MAIN_PAIR));
}

/*
	Draws a border to the screen
*/
void drawBorder(int numRows, int numCols) {
	//main Program here
	for (int i = 0; i < numCols; i++) {
		//top border
		mvaddch(1, i, ACS_CKBOARD);

		//bottom border
		mvaddch(numRows - 2, i, ACS_CKBOARD);
	}

	for (int i = 0; i < numRows; i++) {
		//left column border
		mvaddch(i, 0, ACS_CKBOARD);

		//right column border
		mvaddch(i, numCols - 1, ACS_CKBOARD);
	}
}

/*
	Sets up the color pairs so we can use the COLOR_*_PAIR defines later. 
*/
void initColor(void){
	start_color();
	init_pair(COLOR_MAIN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_TITLE_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_STATUS_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_MENU_PAIR, COLOR_GREEN, COLOR_BLACK);
}