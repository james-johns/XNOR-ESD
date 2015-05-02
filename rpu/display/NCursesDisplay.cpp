

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
		wprintw(menuWin, "\nMenu");
		wrefresh(menuWin);
		menuDirty = false;
	}
	if (playbackDirty) {
		wprintw(playWin, "\nPlay");
		wrefresh(playWin);
		playbackDirty = false;
	}
	if (trackInfoDirty) {
		wprintw(trackWin, "\nTrack");
		wrefresh(trackWin);
		trackInfoDirty = false;
	}
}
