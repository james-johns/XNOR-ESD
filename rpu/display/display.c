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
char displayOptionMode[1] = {254};
char displayLineOneSelect[1] = {128};
char displayLineTwoSelect[1] = {192};
char lineTwoSelect[1] = {192};
char displayClear[1]= {1};
char brightnessLevel[1]={150};

int displayMode;
char userInput;
char usbOutput;
int deviceOpen =0;
int stringSize;
char *testString="Test Complete";
int blockNumber;
char eblock1[1]={129};
char eblock2[1]={136};
char eblock3[1]={192};
char eblock4[1]={200};

char *displayErrorMessage1="please "; 
char *displayErrorMessage2="enter a "; 
char *displayErrorMessage3="valid PI";
char *displayErrorMessage4="N number"; 
char *displayContent1="p       ";
char *displayContent2="Exhibit ";
char *displayContent3="no.1234 ";
char *displayContent4="language: German ";
char *displayContent5=": German";

//update modifed blocks
void refresh(int blockNumber,char *displayContent1,char *displayContent2,char *displayContent3,char *displayContent4,char *displayContent5)
{
char blockNumber1[1]={128};
  char blockNumber2[1]={129};
  char blockNumber3[1]={137};
  char blockNumber4[1]={192};
  char blockNumber5[1]={200};

switch(blockNumber)
    {
    case 1://if refering to block one :playback status
      printf("entering blockNumber 1");
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber1,sizeof(blockNumber1));
      write(displayDevice,displayContent1,sizeof(displayContent1));
      sleep(1);
      break;
      
    case 2://1st part of line 1:track information
      printf("entering blockNumber 2\n");
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber2,sizeof(blockNumber2));
      write(displayDevice,displayContent2,sizeof(displayContent2));
      sleep(1);
      break;
    
    case 3://2nd half of line 1:track information
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber3,sizeof(blockNumber3));
      write(displayDevice,displayContent3,sizeof(displayContent3));
      sleep(1);
      break;

    case 4://1st half of line 2: menu Options
      printf("entering blockNumber 3\n");
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber4,sizeof(blockNumber4));
      write(displayDevice,displayContent4,sizeof(displayContent4));
      sleep(1);
      break;

    case 5://2nd half of line 2: menu Options
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber5,sizeof(blockNumber5));
      write(displayDevice,displayContent5,sizeof(displayContent5));
      sleep(1);
      break;
    }
}

void setBlock( )
{
  

  
      
     
    
 

}

void displayError(char *DisplayErrorMessage1,char *DisplayErrorMessage2,char *DisplayErrorMessage3,char *DisplayErrorMessage4)
{
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,eblock1,sizeof(eblock1));
  write(displayDevice,displayErrorMessage1,sizeof(displayErrorMessage1));
  
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,eblock2,sizeof(eblock2));
  write(displayDevice,displayErrorMessage2,sizeof(displayErrorMessage2));
  
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,eblock3,sizeof(eblock3));
  write(displayDevice,displayErrorMessage3,sizeof(displayErrorMessage3));
  
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,eblock4,sizeof(eblock4));
  write(displayDevice,displayErrorMessage4,sizeof(displayErrorMessage4));
  
}

void initDevice()
{
  char *introString1= " system ";
  char *introString2="by XNOR ";
  char  blockNumber1[1] = {128};
  char  blockNumber2[1] = {136};

  printf("opening ttyUSB0\n");
  displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
  if( displayDevice == -1)
    {
      printf( "Cannot open USB device on /dev/ttyusb0\n\n");
      return;
    }
  printf("file opened\n");
  printf("%s",introString1);
 printf("%s\n",introString2);
  deviceOpen=1;
  
  
  tcgetattr(displayDevice, &options);
  
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);
  tcsetattr(displayDevice, TCSANOW, &options);

//display will enter option mode and wait for the next sspecial character.
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  //special command to clear the display screen
  write(displayDevice,displayClear,sizeof(displayClear));
  //place cursor to first character of line 1 to start again.
  write(displayDevice,displayLineOneSelect,sizeof(displayLineOneSelect));

  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber1,1);
  write(displayDevice,introString1,sizeof(introString1));
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  write(displayDevice,blockNumber2,1);
  write(displayDevice,introString2,sizeof(introString2));
  sleep(5);
   

}

void clearDisplay()
{
 //display will enter option mode and wait for the next sspecial character.
  write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
  //special command to clear the display screen
  write(displayDevice,displayClear,sizeof(displayClear));
  //place cursor to first character of line 1 to start again.
  write(displayDevice,displayLineOneSelect,sizeof(displayLineOneSelect));
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
 printf("initialise Device\n");
  initDevice();
  printf("clear display\n");
  clearDisplay();

 while(1)
    {
      userInput=0;
      printf("\nSelect Option\n");
      printf("[1] refrsh first block\n");
      printf("[2] refrsh second block\n");
      printf("[3] refrsh third block\n");
      printf("[3] refrsh fourth block\n");
      printf("[3] refrsh fifth  block\n");
      scanf("%c",&userInput);
      getchar();
      switch(userInput)
	{
	case '1':
	  displayMode=1;
	  break;
	  
	case '2':
	  displayMode=2;
	  break;
	  
	case '3':
	  displayMode=3;
	  break;

	case '4':
	  displayMode=4;
	  break;
	
	case '5':
	  displayMode=5;
	  break;
	}
   
  printf("refresh data block\n");
 refresh(displayMode,displayContent1,displayContent2,displayContent3,displayContent4,displayContent5);
 sleep(5);
 // printf("clear display\n");
 // clearDisplay();
 // printf("show error\n"); 
 // displayError(displayErrorMessage1,displayErrorMessage2,displayErrorMessage3,displayErrorMessage4); 
 // sleep(10);
	}
  return 0;
}
