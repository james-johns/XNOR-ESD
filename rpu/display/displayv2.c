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
struct termios options;
char displayOptionMode[1] = {254};
char userInput;
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
 




int main (int argc, char **argv)
{
 printf("initialise Device\n");
  initDevice();
  printf("clear display\n");
  clearDisplay();

 while(1)
    {
      userInput=0;
      printf("\nSelect Option\n");
      printf("[1] refresh first block\n");
      printf("[2] refresh second block\n");
      printf("[3] refresh third block\n");
      printf("[3] refresh fourth block\n");
      printf("[3] refresh fifth block\n");
      scanf("%c",&userInput);
      getchar();
      switch(userInput)
	{
	case '1':
	  displayBlock=1;
	  break;
	  
	case '2':
	  displayBlock=2;
	  break;
	  
	case '3':
	  displayBlock=3;
	  break;

	case '4':
	  displayBlock=4;
	  break;
	
	case '5':
	  displayBlock=5;
	  break;
	}
   
  printf("refresh data block\n");
 refresh(displayBlock,displayContent1,displayContent2,displayContent3,displayContent4,displayContent5);
 sleep(5);
 // printf("clear display\n");
 // clearDisplay();
 // printf("show error\n"); 
 // displayError(displayErrorMessage1,displayErrorMessage2,displayErrorMessage3,displayErrorMessage4); 
 // sleep(10);
	}
  return 0;
}
