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

#define DISPLAY_STR_LEN 255



int displayDevice;
int i;
char displayString [DISPLAY_STR_LEN];
struct termios options;
char splashOption[1] = {0x09};
char selectOptions[1] = {254};
char lineTwoSelect[1] = {192};

char brightnessLevel[1]={150};

char userInput;
char usbOutput;
int deviceOpen =0;
int stringSize;
char *testString="Test Complete";


void initDevice()
{
  char *introString= "XNOR";

  printf("opening ttyUSB0\n");
  displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
  if( displayDevice == -1)
    {
      printf( "Cannot open USB device on /dev/ttyusb0\n\n");
      return;
    }
  printf("file opened\n");
  printf("%s\n",introString);
  deviceOpen=1;
  
  
  tcgetattr(displayDevice, &options);
  
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  tcsetattr(displayDevice, TCSANOW, &options);
  
   write(displayDevice,introString,4);
  
  

}

void clearDisplay()
{
  char lineOneSelect[1]= {192};

  write(displayDevice,selectOptions,sizeof(selectOptions));
  write(displayDevice,lineOneSelect,sizeof(lineOneSelect));
  write(displayDevice,("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"),31);
}


void moveCursor(int charNumber)
{
char selectOptions[1] = {254}
char characterNumber = charNumber+127
write(displayDevice,selectOptions,sizeof(selectOptions));

}


void doUpdate()
{


}

 



void displayUpdate (int displayUpdate,char *trackname)
{
  switch(displayUpdate)
    {
    case 1://Login Error
      
      break;
      
    case 2://Playback Request Error
      
      break;
      
    case 3://Generic Error
      
      break;
      
    case 4://welcome message
      
      break;
      
    case 5://Display track Info
      
      break;
      
    case 6://Display Menu
      
      break;
 
    default:
      
      break;
    }
}



int main (int argc, char **argv)
{/*
  do 
  {
    printf("Which USB device is the display\n");
    printf("[1] USB0\n");
    printf("[2] USB1\n");
    printf("[3] USB2\n");
    printf("[4] USB3\n");
    printf("[5] Debug Mode\n");
    scanf("%c",&usbOutput);
    getchar();
    printf("option chosen: %d\n",usbOutput);
    
    
    switch(usbOutput)
      {
      case '1':
	printf("opening ttyUSB0\n");
	displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    break;
	  }
	printf("file opened\n");
	deviceOpen=1;
	break;
	
      case '2':
	printf("opening ttyUSB1\n");
	displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    break;
	  }
	printf("file opened\n");
	deviceOpen=1;
	break;
	
      case '3':
	printf("opening ttyUSB2\n");
	displayDevice = open("/dev/ttyUSB2", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	    break;
	  }
	printf("file opened\n");
	deviceOpen=1;
	break;
	
      case '4':
	printf("opening ttyUSB3\n");
	displayDevice = open("/dev/ttyUSB3", O_RDWR) ;
	if( displayDevice == -1)
	  {
	    printf( "Cannot open USB device on /dev/ttyusb0\n\n");
	      break;
	  }
	  printf("file opened\n");
	  deviceOpen=1;
	  break;

      case '5':
	printf("Entering Debug Mode\n");	 
	printf("opening results.txt\n");
	
	displayDevice = open("results.txt", O_RDWR) ; // open file for writing.
	if( displayDevice == -1)
	  {
	    printf( "Cannot open results.txt\n\n");
	    return 0;
	  }
	printf("file opened\n");
	deviceOpen=1;
	break;
	
      default:
	printf("input not recognised\n");
	userInput=0;
	break;
      }
  } while (deviceOpen==0);
  
    
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
     scanf("%c",&userInput);
      getchar();
      switch(userInput)
	{
	case '1':
	  printf("Enter text to send to display: ");
	  fgets(displayString,DISPLAY_STR_LEN,stdin);
	  printf("String Entered : %s\n",displayString);
	  stringSize = strlen(displayString);
	  printf("String Size : %d\n",stringSize);
	  if(displayString[stringSize-1] == '\n')
	    {
	      displayString[stringSize-1] = ' ';
	    }

	  //  write(displayDevice,selectOptions,sizeof(selectOptions));
	  //write(displayDevice,lineOneSelect,sizeof(lineOneSelect));

	  write(displayDevice,displayString,stringSize);
	  break;   
	  
	case '2':
	  write(displayDevice,selectOptions,sizeof(selectOptions));
	  write(displayDevice,lineTwoSelect,sizeof(lineTwoSelect));
	  write(displayDevice,testString,sizeof(testString));
	  break;
	  
	case '3':
	  write(displayDevice,selectOptions,sizeof(selectOptions));
	  write(displayDevice,splashOption,sizeof(splashOption));
	  break;

	  
	case '4':
	  write(displayDevice,selectOptions,sizeof(selectOptions));
	  write(displayDevice,brightnessLevel,sizeof(brightnessLevel));
	  break;
	  
	case '5':
	  write(displayDevice,selectOptions,sizeof(selectOptions));
	  write(displayDevice,lineTwoSelect,sizeof(lineTwoSelect));
	  write(displayDevice,clearDisplay,sizeof(clearDisplay));
	  write(displayDevice,("                                "),32);
	  break;
	  
	default:
	  printf("input not recognised\n");
	  break;
	}
      
    }
 */
  
  initDevice();
  sleep(2);
  clearDisplay();
  return 0;
}
