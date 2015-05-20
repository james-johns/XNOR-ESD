

#ifndef _NCURSES_DISPLAY_H_
#define _NCURSES_DISPLAY_H_

#include <curses.h>

#include <Display.h>

class NCursesDisplay : public Display {
public:
	NCursesDisplay();
	~NCursesDisplay();

	void refresh();
private:
	WINDOW *menuWin, *trackWin, *playWin, *errorWin;
};

#endif
