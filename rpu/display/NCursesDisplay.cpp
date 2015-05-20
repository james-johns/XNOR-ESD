

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
	char *errorString;
	if (errorIsDirty()) {
		getErrorString(&errorString);

		wclear(errorWin);
		if (errorString != NULL) wprintw(errorWin, errorString);
		wrefresh(errorWin);

		delete errorString;
		setErrorDirty(false);
	}

	char *menuString;
	if (menuIsDirty()) {
		getMenuString(&menuString);

		wclear(menuWin);
		if (menuString != NULL) wprintw(menuWin, menuString);
		wrefresh(menuWin);
		
		delete menuString;
		setMenuDirty(false);
	}

	char *playbackString;
	if (playbackIsDirty()) {
		getPlaybackString(&playbackString);
		wclear(playWin);
		if (playbackString != NULL) wprintw(playWin, playbackString);
		wrefresh(playWin);
		
		delete playbackString;
		setPlaybackDirty(false);
	}

	char *trackInfoString;
	if (trackInfoIsDirty()) {
		getTrackInfoString(&trackInfoString);

		wclear(trackWin);
		if (trackInfoString != NULL) wprintw(trackWin, trackInfoString);
		wrefresh(trackWin);

		delete trackInfoString;
		setTrackInfoDirty(false);
	}
	wrefresh(stdscr);
}
