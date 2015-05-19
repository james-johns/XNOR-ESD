
//set up librarys
#include <stdio.h>
#include <LCDDisplay.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	int i=0; // initialise variable I as 0

	i = atoi(argv[1]); //make I equal to the 1st argument passed with the program actiavtion
	
	// printf("value of I: %d\n",i);//debug string

	//Creates a variable array of test Strings
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
  


	printf("testing display\n");//debug Strings
	LCDDisplay *display = new LCDDisplay();//creates a new instance of the display
	

	
	// I - the argument passed , while the conentents of testString[i] is not null:
	for (;testString[i] != NULL;i++){
		if (strlen(testString[i]) > 1){//if the length of the test String is greater than 1
			display->setTrackInfoString(testString[i]);//write the test String to the track info region
			display->setMenuString(testString[i]);//write the test String to the menu region
		}
		else{
                        //if only 1 character write to the playback string region
			display->setPlaybackString(testString[i]);
		}
	
		time_t currentTime, startTime = (time(NULL));//record the current time in seconds

		do {
			display->refresh();//call the refresh function for the display
			currentTime = time(NULL);//save the current time the function is called
			usleep(50000);//delay for half a second
		}while((strlen(testString[i])*1)+startTime > currentTime);
                //do this code block for at least the time it takes to display the length of the string
	}
  
	delete display; // delete the instance of the display
	printf("Done\n");//debug statement
	return 0; //return 0 
}
