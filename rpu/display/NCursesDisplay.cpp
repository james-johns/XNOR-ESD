

#include <curses.h>

#include <NCursesDisplay.h>


NCursesDisplay::NCursesDisplay() : Display()
{
	initscr();
	menuWin = newwin(1, 64, 0, 0);
	playWin = newwin(1, 64, 1, 0);
	trackWin = newwin(1, 64, 2, 0);
	errorWin = newwin(3, 64, 0, 64);
}

NCursesDisplay::~NCursesDisplay()
{
	delwin(menuWin);
	delwin(playWin);
	delwin(trackWin);
	delwin(errorWin);
	endwin();
}

void NCursesDisplay::refresh()
{
	if (errorDirty) {
		wclear(errorWin);
		if (errorString != NULL) wprintw(errorWin, errorString);
		wrefresh(errorWin);
		errorDirty = false;
	}
	if (menuDirty) {
		wclear(menuWin);
		if (menuString != NULL) wprintw(menuWin, menuString);
		wrefresh(menuWin);
		menuDirty = false;
	}
	if (playbackDirty) {
		wclear(playWin);
		if (playbackString != NULL) wprintw(playWin, playbackString);
		wrefresh(playWin);
		playbackDirty = false;
	}
	if (trackInfoDirty) {
		wclear(trackWin);
		if (trackInfoString != NULL) wprintw(trackWin, trackInfoString);
		wrefresh(trackWin);
		trackInfoDirty = false;
	}
	wrefresh(stdscr);
}
