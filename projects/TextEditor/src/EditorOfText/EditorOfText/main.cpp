#define PDC_DLL_BUILD 1
#define MENU_ITEM_RATIO 10
#define COLOR_MAIN_PAIR 1
#define COLOR_TITLE_PAIR 2
#define COLOR_STATUS_PAIR 3

#include "curses.h"
#include <string>
#include <iostream>
using namespace std;

void initColor(void);
void drawBorder(int, int);
//WINDOW* setupWindow(int, int);
void drawMenu(int, int);
void drawStatus(int, int);


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

	drawBorder(numRows, numCols);
	drawMenu(numRows, numCols);
	drawStatus(numRows, numCols);
	

	refresh(); //Tells Curses to Draw

	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	//char result = getch();
	char pause;
	cin >> pause;
	endwin();

	return 0;
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
	Draws a menu to the screen
*/
void drawMenu(int numRows, int numCols){
	int xoffset = 1;
	string menuItems[5] = { "File", "Edit", "View", "Tools", "Help" };
	//loop through and print menu items
	attron(COLOR_PAIR(COLOR_TITLE_PAIR));
	for (int i = 0; i <= menuItems->length(); i++) {
		mvaddstr(0, ((numCols / MENU_ITEM_RATIO) * i) + xoffset, menuItems[i].c_str());
	}
	attroff(COLOR_PAIR(COLOR_TITLE_PAIR));
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

void initColor(void){
	start_color();
	init_pair(COLOR_MAIN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_TITLE_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_STATUS_PAIR, COLOR_GREEN, COLOR_BLACK);
}