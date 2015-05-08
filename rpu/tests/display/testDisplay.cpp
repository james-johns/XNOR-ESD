

#include <stdio.h>
#include <LCDDisplay.h>

int main(int argc, char **argv)
{
	printf("testing display");
	LCDDisplay *display = new LCDDisplay();

	display->refresh();

	display->setMenuString("test string");
	display->refresh();

	display->setMenuString("new string");
	display->setTrackInfoString("track string");
	display->refresh();

	delete display;
	printf("Done");
	return 0;
}
