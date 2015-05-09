

#ifndef _LCDDISPLAY_H_
#define _LCDDISPLAY_H_

#include <Display.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

class LCDDisplay : public Display {
public:
	LCDDisplay();
	~LCDDisplay();

	void refresh();
	
private:
};

#endif
