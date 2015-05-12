

#include <stdio.h>
#include <LCDDisplay.h>

int main(int argc, char **argv)
{
  printf("testing display\n");
  LCDDisplay *display = new LCDDisplay();
  display->setPlaybackString("p");
  display->refresh();
  display->setPlaybackString("s");
  //printf("track string\n");
  display->setTrackInfoString("Now Playing: Exhibit ID 1010");
  display->refresh();
 
 //	display->setTrackInfoString("supercalafragalisticexpialodocious\n");	
  //	printf("new string\n");
  display->setMenuString("Select Language?");
		
  display->refresh();
  display->setMenuString("Language Choice: Cornish");
  //	printf("test string\n");
  display->refresh();
  display->setPlaybackString("R");
  display->refresh();
  display->displayError("ERROR: Unrecognised PIN Entered");
  display->refresh();
  
delete display;
   printf("Done\n");
  return 0;
}
