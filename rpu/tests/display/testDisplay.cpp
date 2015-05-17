

#include <stdio.h>
#include <LCDDisplay.h>

int main(int argc, char **argv)
{
	printf("testing display\n");
	LCDDisplay *display = new LCDDisplay();
	display->setPlaybackString("p");
	display->refresh();
  
	display->setTrackInfoString("Now Playing: Exhibit ID 1010");
	display->refresh();
	display->setTrackInfoString("12:37 / 17:00");
	display->refresh();
	sleep(5);//imitates wait between listening and button press.
	display->setPlaybackString("w");
	display->setMenuString("Select Language?");	
	display->refresh();
	display->setMenuString("Language:English");
	display->refresh();
	display->setMenuString("Language:French");
	display->refresh();
	display->setMenuString("Language:German");
	display->refresh();
	display->setPlaybackString("r");
	display->setTrackInfoString("Rewind");
	display->refresh();
	display->setMenuString("Select Info Lvl?");
	display->refresh();
	display->setMenuString("Ilevel:Child");
	display->refresh();
	display->setMenuString("Ilevel:Teenager");
	display->refresh();
	display->setMenuString("Ilevel:Adult");
	display->refresh();
	display->setPlaybackString("f");
	display->setTrackInfoString("Fastforward");
	display->refresh();
	display->displayError("Unrecognised PIN Entered");
	display->refresh();
	display->displayError("Invalid Exhibit ID entered");
	display->refresh();
	display->displayError("Wireless Signal Lost");
	display->refresh();
	display->displayError("Thanks for using  XNOR M.A.D.S");
	display->refresh();
	delete display;
	printf("Done\n");
	return 0;
}
