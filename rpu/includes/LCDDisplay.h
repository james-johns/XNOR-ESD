

#ifndef _LCDDISPLAY_H_
#define _LCDDISPLAY_H_

#include <Display.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

struct displayBlock {
	int start, length, scrollPosition;
struct timeval lastTime;
};

class LCDDisplay : public Display {
public:
	LCDDisplay();
	~LCDDisplay();

	void refresh();
	bool isConnected();
private:
	void writeBlock(int block, char *inputString);

	int displayDevice; // file descriptor of connected device
	struct displayBlock *blocks;

	unsigned char displayOptionMode; // special control character for configuring display
	char displayClear; // character to write after displayOptionMode to clear the entire display

};

#endif
