

#include <LCDDisplay.h>


//set up variables
char displayOptionMode[1] = {254};//special char that puts the display into a mode waiting for the next character to define which option is needed.
char displayClear[1] = {1};
struct termios options;
int displayDevice;
int currentChar;
int i,j,k,l;

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
  char blockNumber3[1]={192};//10th character of the display
 
  
  char trackOutputString [4][15];
  char menuOutputString [4][16];
  char errorOutputString [4][16];
  int tokenNumber=0;
  int j=0;

  if (playbackDirty == true & playbackString != NULL)
    {
      std::cout << "writing playback String\n";
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      write(displayDevice,blockNumber1,sizeof(blockNumber1));
      write(displayDevice,playbackString,1);
      playbackDirty = false;
      
    }



  if (trackInfoDirty == true & trackInfoString != NULL)
    {
      j=0;
      tokenNumber=0;
      std::cout << "writing track Info  String\n";
      std::cout <<"size of trackinfo string: " << strlen(trackInfoString) << "\n";
      for ( i=0;i <= strlen(trackInfoString);i++)
	{
	  
	  // std::cout << "current char number: " << j <<"\n";
	    std::cout << "current char : " << trackInfoString[i] <<"\n";
	  trackOutputString[tokenNumber][i] =  trackInfoString[i];
	     std::cout << "copied char : " << trackOutputString[tokenNumber][i] <<"\n";
	  j++;
	  if (j==15)
	    {
	      std::cout << "new string created\n";
	      std::cout << "string Created : " << trackOutputString[tokenNumber] <<"\n";
	      tokenNumber++;

	      j=0;
	    }
	}
      
      std::cout << "number of Strings = " << tokenNumber+1 << "\n";
      for(int k=0;k<=tokenNumber;k++)
	{
	  if (trackOutputString[k] != NULL)
	    {
	      std::cout << "current string : " << trackOutputString[k] <<"\n";
	      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
	      write(displayDevice,blockNumber2,sizeof(blockNumber2));
	      write(displayDevice,trackOutputString[k],strlen(trackOutputString[k]));
	      sleep(5);
	    }
	}
      trackInfoDirty = false;  
    }
  

  if (menuDirty == true & menuString != NULL)
    {
      tokenNumber=0;
      j=0;
      std::cout << "writing menu String\n";
      std::cout <<"size of menu string: " << strlen(menuString) << "\n";
      for (int i=0;i <= strlen(menuString);i++)
	{
	  //std::cout << "current char number: " << j <<"\n";
	  std::cout << "current char : " << menuString[i] <<"\n";
	  menuOutputString[tokenNumber][i] =  menuString[i];
	   std::cout << "copied char : " << menuOutputString[tokenNumber][i] <<"\n";
	  j++;
	  if (j==16)
	    {
	      std::cout << "new string created\n";
	      tokenNumber++;
	      j=0;
	    }
	}
     

      /*  if (menuOutputString[tokenNumber][15]=="/r")
	  {
	  menuOutputString[tokenNumber][15]=" ";
	  }*/

      std::cout << "number of Strings = " << tokenNumber+1 << "\n";
      for(int k=0;k<=tokenNumber;k++)
	{
	  if (menuOutputString[k] != NULL)
	    {
	      std::cout << "current string : " << menuOutputString[k] <<"\n";
	      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
	      write(displayDevice,blockNumber3,sizeof(blockNumber3));
	      write(displayDevice,menuOutputString[k],strlen(menuOutputString[k]));
	      sleep(5);
	    }
	}
      menuDirty = false;  
    }

  if (errorString != NULL)
    {
      tokenNumber=0;
      j=0;
      
      //display will enter option mode and wait for the next sspecial character.
      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
      //special command to clear the display screen
      write(displayDevice,displayClear,sizeof(displayClear));

      std::cout << "writing Error Message\n";
      std::cout <<"size of Error Message: " << strlen(errorString) << "\n";
      for (int i=0;i <= strlen(errorString);i++)
	{
	  // std::cout << "current char number: " << j <<"\n";
	  std::cout << "current char : " << menuString[i] <<"\n";
	  errorOutputString[tokenNumber][i] =  errorString[i];
	   std::cout << "copied char : " << menuOutputString[tokenNumber][i] <<"\n";
	  j++;
	  if (j==16)
	    {
	      std::cout << "new string created\n";
	      tokenNumber++;
	      j=0;
	    }
	}
     

      /*  if (menuOutputString[tokenNumber][15]=="/r")
	  {
	  menuOutputString[tokenNumber][15]=" ";
	  }*/

      std::cout << "number of Strings = " << tokenNumber+1 << "\n";
      for(int k=0;k<=tokenNumber;k++)
	{
	  if (errorOutputString[k] != NULL)
	    {
	      std::cout << "current string : " << errorOutputString[k] <<"\n";
	      write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
	      write(displayDevice,blockNumber1,sizeof(blockNumber1));
	      write(displayDevice,errorOutputString[k],strlen(errorOutputString[k]));
	      sleep(10);
	    }
	}
      errorString = NULL;  



    }
}
