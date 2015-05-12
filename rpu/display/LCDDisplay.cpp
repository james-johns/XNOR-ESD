

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
 
  
	char trackOutputString [4][16];
	char menuOutputString [4][16];
	char errorOutputString [4][32];
	int tokenNumber;
	int j=0;

	for (int i=0;i>4;i++) {
		trackOutputString[i][0]=0;
		menuOutputString[i][0]=0;
		errorOutputString[i][0]=0;
	}
 


		if (playbackDirty == true & playbackString != NULL)
		{
		std::cout << "writing playback String\n";
		write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
		write(displayDevice,blockNumber1,sizeof(blockNumber1));
		write(displayDevice,playbackString,1);
		playbackDirty = false;
      	}

  		if (trackInfoDirty == true & trackInfoString != NULL){
		j=0;
		tokenNumber=0;
		std::cout << "writing track Info String\n";
		std::cout <<"size of the trackinfo string: " << strlen(trackInfoString) << "\n";
		int tokenSize = strlen(trackInfoString);
		std::cout <<"tokenSize: " << tokenSize << "\n";
	
		for (int i = 0; i < tokenSize; i += 15) {
		std::cout << "current i value: " << i <<"\n";
		int tokenLength = (((tokenSize - i) >= 15) ? 15 : (tokenSize - i));
		strncpy(trackOutputString[i/15], trackInfoString + i, tokenLength);
		trackOutputString[i/15][tokenLength] = '\0';
		std::cout << "tokenNumber: " << tokenNumber << "\n";
		tokenNumber++;
	}
		tokenNumber--;

		if(strlen(trackOutputString[tokenNumber]) <15){

		for (int l=strlen(trackOutputString[tokenNumber]);l<15;l++){
		trackOutputString[tokenNumber][l] = ' ';
	}
	}
		
	      
     
 
      

		for(int k=0;k<=tokenNumber;k++){
		
		if (trackOutputString[k][0] != 0){

		std:: cout << " string contents: " << trackOutputString[k] <<"\n";
		write(displayDevice,displayOptionMode,sizeof(displayOptionMode));
		write(displayDevice,blockNumber2,sizeof(blockNumber2));
		write(displayDevice,trackOutputString[k],strlen(trackOutputString[k]));
		sleep(5);
	}
	}
		trackInfoDirty = false;  
	}
	
	
		if (menuDirty == true & menuString != NULL){
		tokenNumber=0;
		j=0;
		std::cout << "writing menu String\n";
		std::cout <<"size of the menu string: " << strlen(menuString) << "\n";
		for (int i=0;i <= strlen(menuString);i++){
		
		//std::cout << "current char number: " << j <<"\n";
		// std::cout << "current char of menu String : " << menuString[i] <<"\n";
		menuOutputString[tokenNumber][i] =  menuString[i];
		//std::cout << "copied char to menuOutput String : " << menuOutputString[tokenNumber][i] <<"\n";
	 
		// std::cout << "current token Number: " << tokenNumber << "\n";
		if (j==15)
		{
		std::cout << "new string created\n";
		//std::cout << "String Created : " << menuOutputString[tokenNumber] << "\n";
		tokenNumber++;
	     
		j=0;
	}
		j++;
	}
     
		if(strlen(menuOutputString[tokenNumber]) <15)
		{
		for (int l=strlen(menuOutputString[tokenNumber]);l<15;l++)
		{
		menuOutputString[tokenNumber][l] = ' ';
	}
	}

		std::cout << "number of Strings = " << tokenNumber << "\n";
	  
		for(int k=0;k<=tokenNumber+1;k++)
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
		//std::cout << "current char : " << menuString[i] <<"\n";
		errorOutputString[tokenNumber][i] =  errorString[i];
		// std::cout << "copied char : " << menuOutputString[tokenNumber][i] <<"\n";
		j++;
		/*if (j==15)
		  {
		  std::cout << "new string created\n";
		  tokenNumber++;
		  j=0;
		  }*/
	}
     

		if(strlen(errorOutputString[tokenNumber]) <15)
		{
		for (int l=strlen(errorOutputString[tokenNumber]);l<15;l++)
		{
		errorOutputString[tokenNumber][l] = ' ';
	}
	} 

		std::cout << "number of Strings = " << tokenNumber+1 << "\n";
		for(int k=0;k<=tokenNumber+1;k++)
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
