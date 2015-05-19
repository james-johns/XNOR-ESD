

#include <stdio.h>
#include <LCDDisplay.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	int i=0;

	 i = atoi(argv[1]);
	
	 printf("value of I: %d\n",i);

  char const* testString[]={
	  "p",
	  "w",
	  "r",
	  "f",  
	  "Now Playing: EX9876",
	  "Now playing: EX1234",
	  "Rewind",
	  "Fastforward",
	  "Select Language?",
	  "Language:English",
	  "Language:Spanish",
	  "Language:German",
	  "Select Info Lvl?",
	  "Ilevel:Child",
	  "Ilevel:Teenager",
	  "Ilevel:Adult",
	  "Unrecognised PIN Entered",
	  "Invalid Exhibit ID entered",
	  "Wireless Signal Lost",
	  "Thanks for using  XNOR M.A.D.S",
	  (char *)NULL};
  


	printf("testing display\n");
	LCDDisplay *display = new LCDDisplay();
	

	//change i to = argv define i outside of the forloop

for (;testString[i] != NULL;i++){
  if (strlen(testString[i]) > 1){
    display->setTrackInfoString(testString[i]);
    display->setMenuString(testString[i]);
  }
  else{
    display->setPlaybackString(testString[i]);
  }
	
	time_t currentTime, startTime = (time(NULL));

	do {
	display->refresh();
	currentTime = time(NULL);
	usleep(50000);
	}while((strlen(testString[i])*1)+startTime > currentTime);
 }
  
	delete display;
	printf("Done\n");
	return 0;
}
