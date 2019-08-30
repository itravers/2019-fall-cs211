#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>
using namespace std;

int main(void) {

	//Initialze Curses
	WINDOW* mainWindow = nullptr;
	int numRows = 0;
	int numCols = 0;

	//initialize screen to begin curses mode
	mainWindow = initscr();

	//go near-full screen
	getmaxyx(mainWindow, numRows, numCols);
	resize_term(numRows - 1, numCols - 1);
	getmaxyx(mainWindow, numRows, numCols);

	//turn off key echo
	noecho();
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	curs_set(0);

	//main Program here
	for (int i = 0; i < numCols; i++){
		//top border
		mvaddch(0, i, 219);

		//bottom border
		mvaddch(numRows - 1, i, 219);
	}

	for (int i = 0; i < numRows; i++) {
		//left column border
		mvaddch(i, 0, 219);

		//right column border
		mvaddch(i, numCols - 1, ACS_CKBOARD);

	}

	refresh(); //Tells Curses to Draw

	//revert back to normal console mode
	nodelay(mainWindow, TRUE);
	keypad(mainWindow, TRUE);
	mvaddstr(0, 0, "Press ANYKEY to continue...");
	char result = getch();
	endwin();

	return 0;
}