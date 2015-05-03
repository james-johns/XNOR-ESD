

#include <curses.h>

#include <NCursesDisplay.h>


NCursesDisplay::NCursesDisplay() : Display()
{
	initscr();
	menuWin = newwin(1, 64, 0, 0);
	playWin = newwin(1, 64, 1, 0);
	trackWin = newwin(1, 64, 2, 0);
}

NCursesDisplay::~NCursesDisplay()
{
	delwin(menuWin);
	delwin(playWin);
	delwin(trackWin);
	endwin();
}

void NCursesDisplay::refresh()
{
	if (menuDirty) {
		wclear(menuWin);
		wprintw(menuWin, menuString);
		wrefresh(menuWin);
		menuDirty = false;
	}
	if (playbackDirty) {
		wclear(playWin);
		wprintw(playWin, playbackString);
		wrefresh(playWin);
		playbackDirty = false;
	}
	if (trackInfoDirty) {
		wclear(trackWin);
		wprintw(trackWin, trackInfoString);
		wrefresh(trackWin);
		trackInfoDirty = false;
	}
	wrefresh(stdscr);
}
