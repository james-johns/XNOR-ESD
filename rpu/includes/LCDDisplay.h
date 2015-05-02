

#ifndef _LCDDISPLAY_H_
#define _LCDDISPLAY_H_

#include <Display.h>

class LCDDisplay : public Display {
public:
	LCDDisplay();
	~LCDDisplay();

	void refresh();
private:
};

#endif
