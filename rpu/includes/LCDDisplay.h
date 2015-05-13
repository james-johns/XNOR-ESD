

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
	int displayDevice; // file descriptor of connected device

	char displayOptionMode; // special control character for configuring display
	char displayClear; // character to write after displayOptionMode to clear the entire display

};

#endif
