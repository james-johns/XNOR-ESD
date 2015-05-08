

#include <LCDDisplay.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>

//set up variables
char displayOptionMode[1] = {254};//special char that puts the display into a mode waiting for the next character to define which option is needed.
char displayClear[1] = {1};
struct termios options;
int displayDevice;


LCDDisplay::LCDDisplay() : Display()
{


   std::cout << "opening ttyUSB0\n";
  displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
  if( displayDevice == -1)
    {
       std::cout << "Cannot open USB device on /dev/ttyusb0\n\n";
      displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
      if( displayDevice == -1)
	{
	  printf( "Cannot open USB device on /dev/ttyusb1\n\n");
	  return;
	}
    }
  std::cout << "file opened\n";

  tcgetattr(displayDevice, &options);
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  tcsetattr(displayDevice, TCSANOW, &options);

  //display will enter option mode and wait for the next sspecial character.
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  //special command to clear the display screen
  write(displayDevice,displayClear,sizeof(displayClear));
 
}

LCDDisplay::~LCDDisplay()
{

}


void LCDDisplay::refresh()
{
  char displayOptionMode[1] = {254};//Special character to enable option mode
  char blockNumber1[1]={128};//first character of the display
  char blockNumber2[1]={129};//2nd character of the display
  char blockNumber3[1]={137};//10th character of the display
  char blockNumber4[1]={192};//17th character of the display
  char blockNumber5[1]={200};//25th character of the display
  
  
 
  




  if (playbackDirty = true)
    {
      
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber1,sizeof(blockNumber1));
      write(displayDevice,playbackString,1);
      playbackDirty = false;
      
    }


  if (trackInfoDirty = true)
    {
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber2,sizeof(blockNumber2));
      write(displayDevice,trackInfoString,sizeof(trackInfoString));
      
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber3,sizeof(blockNumber2));
      write(displayDevice,trackInfoString,sizeof(trackInfoString));
      trackInfoDirty = false;
            
    }
  
  if (menuDirty = true)
    {
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber3,sizeof(blockNumber3));
      write(displayDevice,menuString,sizeof(menuString));

      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber5,sizeof(blockNumber5));
      write(displayDevice,menuString,sizeof(menuString));
      menuDirty = false;
    }
  

  
 
}

void LCDDisplay :: displayError(char *str)
{
  char *errorString = str;
 int currentChar;
 int stringLength = sizeof(*errorString);

for(currentChar=0; currentChar < stringLength; currentChar++)
  {
    
  }

}
