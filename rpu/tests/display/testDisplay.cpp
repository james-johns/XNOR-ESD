

#include <LCDDisplay.h>

int main(int argc, char **argv)
{
  std::cout << "testing display";
	LCDDisplay *display = new Display();

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
