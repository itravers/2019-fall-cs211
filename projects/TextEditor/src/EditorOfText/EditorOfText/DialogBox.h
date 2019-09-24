/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	September 23rd, 2019
*********************************************************************************/
#ifndef DIALOG_BOX
#define DIALOG_BOX

#include "curses.h"
#include "panel.h"
#include <string>

using std::string;

/*******************************************************************************
 * Class Name:   DialogBox
 * Purpose:      The DialogBox is a box that is displayed for the user
                 the user can input to type into the dialog box,
				 once the user hits enter the dialog box input
				 if fed to whereever it should be fed.
 *******************************************************************************/
class DialogBox {
public:

	/*******************************************************************************
	 * Constructor
	 *******************************************************************************/
	DialogBox(WINDOW* parentWindow, string message, int yPos, int xPos, int nRows, int nCols);

	/*******************************************************************************
	 * Public Fields
	 *******************************************************************************/

	 /*******************************************************************************
	  * Public Methods
	  *******************************************************************************/
	//getters
	string getValueFromUser(string message, int yPos, int xPos, int nRows, int nCols);
	void show();
	void hide();
	int getXPos();
	int getYPos();
	int getNumCols();
	int getNumRows();
	string getMessage();
	bool isShowing();
	WINDOW* getWindow();
	PANEL getPanel();

	void draw(); //draws the dialog box window if it is not hidden

	//setters
	void setXPos(int x);
	void setYPos(int y);
	void setNumCols(int c);
	void setNumRows(int r);
	void setMessage(string m);

private:
	/*******************************************************************************
	 * Private Fields
	 *******************************************************************************/
	bool is_showing; /* Is the DialogBox showing? */
	int xPos, yPos, nCols, nRows;
	string message;
	WINDOW* window;
	PANEL* panel;
	
	int numCols; /* The Number of columns the dialog box takes. */
	int numRows; /* The number of rows the dialog box takes. */
	int posX;	 /* The X position of the dialog box. */
	int posY;	/* The Y position of the dialog box. */

	/*******************************************************************************
	 * Private Methods
	 *******************************************************************************/
};
#endif