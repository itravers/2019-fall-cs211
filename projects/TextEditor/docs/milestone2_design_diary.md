# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) 

I need to investigate how to open a file to read and display it's contents in the text editor. Issue #9 will track
the progress of this https://github.com/itravers/2019-fall-cs211/issues/9
It looks like all I needed to do was read a file in line by line into a string vector
Then I loop through the vector printing line by line to the screen.

I need to investigate how to open a file from the command line, and how to debug with curses.
https://github.com/itravers/2019-fall-cs211/issues/16
In visual studio, right click on the project file, not the solution file.
Go to Debugging and under command arguments list your command arguments just as you would from the command line.
I can't just concatanate a char* to a string, I need to figure out how to do that.

I can now trigger the menus's with mouse clicks. I had to create a mouse handler function
that calls the MenuController and has it tell us if this click involves a menu or not.
If this click does involve a menu, we tell the MenuController to processes the click, 
which at this point only opens or closes a menu. Closed github issue:
https://github.com/itravers/2019-fall-cs211/issues/7