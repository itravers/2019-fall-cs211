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

/* Includes */
#include "curses.h"
#include "panel.h"
#include "customcolors.h"
#include "MenuController.h"
#include <string>
#include <iostream>

/* Namespaces */
using std::string;
using std::cin;

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

	int menuHeight = 10;
	int menuWidth = 20;
	
	mvwaddstr(mainWindow, 4, 2, "This is covered up text, i can't see it all.");

	titleWindow = subwin(stdscr, menuHeight, menuWidth, 2, 1);
	colorbox(titleWindow, COLOR_TITLE_PAIR, 1);
	
	int startx, starty, height, width;

	getbegyx(titleWindow, starty, startx);
	getmaxyx(titleWindow, height, width);

	
	mvwaddstr(titleWindow, 0, 2, "File");
	

	
	//resize_window(titleWindow, 2, 2);
	//wrefresh(titleWindow);


	//Initialize Menu Controller
	MenuController::MenuController();

	//Draw the screen
	drawScreen(numRows, numCols);



	//wrefresh(titleWindow);
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
}

/*
	This function was not written by me. I adapted it from the setcolor 
	function in tui.c, supplied by the teacher.
*/
static void setcolor(WINDOW* win, chtype color)
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
	This function was not written by me. I adapted it from the colorbox function in tui.c
	that the teacher supplied.
*/
static void colorbox(WINDOW* win, chtype color, int hasbox)
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
