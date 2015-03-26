/*
  Title  : display.c
  Author : Ryan King
  Date   : 22/03/15
  compilation String :gcc -Wall -o display  display.c 
*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
//Set Variables

int displayDevice;
int i;
char displayString [18];
struct termios options;
char disableSplash[1] = {0x7C};
char splashOption[1] = {0x09};
char blarg[1] = {254};
char blarg2[1] = {192};
char brightness[1]={0x7C};
char brightnessLevel[1]={150};
char clearDisplay[1]= {0x01};
int userInput;
int usbOutput=0;
char *testString="Test Complete";

int main (int argc, char **argv)
{
  do 
  {
    printf("Which USB device is the display\n");
    printf("[1] USB0\n");
    printf("[2] USB1\n");
    printf("[3] USB2\n");
    printf("[4] USB3\n");
    printf("[5] Debug Mode\n");
    scanf("%d",&usbOutput);
    getchar();
    printf("option chosen: %d\n",usbOutput);
    
    
    switch(usbOutput)
      {
      case 1:
	printf("opening ttyUSB0\n");
	displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    return 0;
	  }
	printf("file opened\n");
	break;
	
      case 2:
	printf("opening ttyUSB1\n");
	displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    return 0;
	  }
	printf("file opened\n");
	break;
	
      case 3:
	printf("opening ttyUSB2\n");
	displayDevice = open("/dev/ttyUSB2", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    return 0;
	  }
	printf("file opened\n");
	break;
	
      case 4:
	printf("opening ttyUSB3\n");
	displayDevice = open("/dev/ttyUSB3", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	      return 0;
	  }
	  printf("file opened\n");
	  break;

      case 5:
	printf("Entering Debug Mode\n");	 
	printf("opening results.txt\n");
	
	displayDevice = open("/home/ryan/ESD-RPU/XNOR-ESD/rpu/Display/results.txt", O_RDWR) ; // open file for writing.
	if( displayDevice == -1)
	  {
	    printf( "Cannot open results.txt\n\n");
	    return 0;
	  }
	printf("file opened\n");
	break;
	
      default:
	printf("input not recognised\n");
	userInput=0;
	break;
      }
  } while (usbOutput==0);
  
    
    tcgetattr(displayDevice, &options);
    
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  tcsetattr(displayDevice, TCSANOW, &options);
  
  
  while(1)
    {
      userInput=0;
      printf("\nSelect Option\n");
      printf("[1] Test display output\n");
      printf("[2] Change cursor position\n");
      printf("[3] Remove Splashscreen\n");
      printf("[4] Change screen brightness\n");
      printf("[5] Clear Screen\n");
     scanf("%d",&userInput);
      getchar();
      switch(userInput)
	{
	case 1:
	  printf("Enter text to send to display: ");
	  fgets(displayString,sizeof(displayString),stdin);
	  printf("String Entered : %s\n",displayString);
	  write(displayDevice,displayString,sizeof(displayString));
	  break;
	  
	case 2:
	  write(displayDevice,blarg,sizeof(blarg));
	  write(displayDevice,blarg2,sizeof(blarg2));
	  write(displayDevice,testString,sizeof(testString));
	  break;
	  
	case 3:
	  write(displayDevice,disableSplash,sizeof(displayDevice));
	  write(displayDevice,splashOption,sizeof(displayDevice));
	  break;
	  
	case 4:
	  write(displayDevice,brightness,sizeof(displayDevice));
	  write(displayDevice,brightnessLevel,sizeof(displayDevice));
	  break;
	  
	case 5:
	  write(displayDevice,clearDisplay,sizeof(displayDevice));
	  break;
	  
	default:
	  printf("input not recognised\n");
	  break;
	}
      
    }
  
  
  
  return 0;
}
