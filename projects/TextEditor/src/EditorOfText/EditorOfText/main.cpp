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
#include "FileController.h"
#include <string>
#include <iostream>
#include <stdio.h>

/* Namespaces */
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;

/* Function Prototypes*/
void initColor(void);			// Initialize the Color System
void drawBorder(int, int);		// Border around the screen
void drawStatus(int, int);		// Draws the status bar at the bottom of the screen
void drawScreen(int, int);		// Draws everything associated with the screen.
void changeStatus(string);		// Changes the status screen that gets printed at the bottom.
void writeLines(vector<string>);// Writes the lines from the file to the screen
void processMouseEvent(MEVENT*, int, int);// processes a mouse event
static void colorbox(WINDOW*, chtype, int);


/* Objects */
FileController fileController;
MenuController menuController;
static WINDOW* titleWindow;


/* Variables */
string currentStatus = "Starting Program...";


/* Start of the Program. */
int main(int argc, char* argv[]) {
	string arg1;
	arg1 = argv[1];
	arg1 = "Command Line Argument 1  " + arg1;

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
	//keypad(mainWindow, TRUE);
	curs_set(0);

	//Initialize File Controller
	FileController fileController;

	//Initialize Menu Controller
	MenuController menuController(mainWindow, numRows, numCols);

	//setup mouse
	mousemask(ALL_MOUSE_EVENTS, NULL);

	//read in the file from the command line
	string fileName = argv[1];
	vector<string>lines;
	fileController.readFile(fileName, lines, READ, changeStatus);
	writeLines(lines);
	//changeStatus("test");
	//Draw the screen
	drawScreen(numRows, numCols);

	////set menu open for demo
	//menuController.setMenuState(MENU_VIEW_OPEN);
	
	//Get Keyboard input to control the menu's
	
	MEVENT event;
	int c;
	
	while ((c = wgetch(mainWindow)) != KEY_END) {
		switch (c) {
			
			case ctrl('f'):
				menuController.setMenuState(MENU_FILE_OPEN);
				break;
			case ctrl('e'):
				menuController.setMenuState(MENU_EDIT_OPEN);
				break;
			case ctrl('v'):
				menuController.setMenuState(MENU_VIEW_OPEN);
				break;
			case ctrl('t'):
				menuController.setMenuState(MENU_TOOLS_OPEN);
				break;
			case ctrl('h'):
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
			case KEY_MOUSE:
					//changeStatus("key mouse");
					if (nc_getmouse(&event) == OK) {
						processMouseEvent(&event, numRows, numCols);
					}
				break;
			default:
				break;
			
		}
		refresh();
		drawScreen(numRows, numCols);
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
	mvaddstr(numRows-1, xoffset, currentStatus.c_str());
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

/*
	Changes the current status to a new status.
	Printed at the bottom of screen in status bar.
*/
void changeStatus(string newStatus) {
	currentStatus = newStatus + "                 ";
}

/*
	Writes out the lines in vector to the screen, exactly
	how it was read in
*/
void writeLines(vector<string>lines) {
	int firstLine = 2;
	int margin = 2;
	for (int i = 0; i < lines.size(); i++) {
		mvaddstr(firstLine + i, 2, lines[i].c_str());
	}
}

/*
	Processes a Mouse Event
*/
void processMouseEvent(MEVENT* mouseEvent, int numRows, int numCols) {
	changeStatus("processMouseEvent()");
	if (menuController.isMenuMouseEvent(mouseEvent, numRows, numCols, changeStatus)) {
		menuController.processMouseEvent(mouseEvent, numRows, numCols, changeStatus);
	}
}
