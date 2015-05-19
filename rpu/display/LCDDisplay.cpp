#include <stdlib.h>
#include <stdexcept>
#include <LCDDisplay.h>
#include <sys/time.h>

LCDDisplay::LCDDisplay() : Display()
{	struct termios options;
	displayOptionMode = (unsigned char) 254;
	displayClear = (char) 1;
       

	std::cout << "opening ttyUSB0\n";
	displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
	if( displayDevice == -1) {
		std::cout << "Cannot open USB device on /dev/ttyusb0\n\n";
		displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
		if( displayDevice == -1) {
			std::cout <<  "Cannot open USB device on /dev/ttyusb1\n\n";
		}
	}
	std::cout << "file opened\n";
	
	
	tcgetattr(displayDevice, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	tcsetattr(displayDevice, TCSANOW, &options);

	blocks = (struct displayBlock *) malloc(sizeof(struct displayBlock)*4);
	blocks[0].start = 0;	blocks[0].length = 1;  
	blocks[0].scrollPosition=0; gettimeofday(&blocks[0].lastTime,NULL);
	blocks[1].start = 1;	blocks[1].length = 15; 
	blocks[1].scrollPosition=0; gettimeofday(&blocks[1].lastTime,NULL);
	blocks[2].start = 64;	blocks[2].length = 16; 
	blocks[2].scrollPosition=0; gettimeofday(&blocks[2].lastTime,NULL);
	blocks[3].start = 0;	blocks[3].length = 32; 
	blocks[3].scrollPosition=0; gettimeofday(&blocks[3].lastTime,NULL);

	//special character to enable  option mode, waits for the next special character.
	write(displayDevice, &displayOptionMode, 1);
	//special character to clear the display screen
	write(displayDevice, &displayClear, 1);
	std::cout << "clearing display" << std::endl;
}

LCDDisplay::~LCDDisplay()
{
	close(displayDevice);
}

bool LCDDisplay::isConnected()
{
	return (displayDevice != -1);
}

void LCDDisplay::refresh()
{
	char blockNumber1[1]={128};//first character of the display
	char playbackOutputString[1]={0};
	char playIcon[1]={62};
	char pauseIcon[1]={4};
	char rewindIcon[1]={127};
	char fForwardIcon[1]={126};
	char *playbackString;
	char *trackInfoString;
	char *menuString;
	char *errorString;
	//time_t currentTime = (time(NULL));

	struct timeval currentTime;
	gettimeofday(&currentTime,NULL);

//	if (blocks[0].lastTime < currentTime -1){
	if ((((blocks[0].lastTime.tv_sec*1000000)+blocks[0].lastTime.tv_usec)+500000) < 
	    ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
		setPlaybackDirty(true);

	}

	if (playbackIsDirty() && getPlaybackString(&playbackString) != NULL) {
		std::cout << "playback Button Pressed\n";
		int tokenSize = strlen(playbackString);
      		
		switch(*playbackString){
		case 'p':
			strncpy(playbackOutputString,playIcon,8);
			break;
		case 'w':
			strncpy(playbackOutputString,pauseIcon,8);
			break;
		case 'f':
			strncpy(playbackOutputString,fForwardIcon,8);
			break;
		case 'r':
			strncpy(playbackOutputString,rewindIcon,8);
			break;
		}
		
		write(displayDevice, &displayOptionMode, 1);
		write(displayDevice, &blockNumber1, 1);
		write(displayDevice, playbackOutputString, 1);
		delete playbackString;
		setPlaybackDirty(false);
	}

	if (trackInfoIsDirty()==true){
		blocks[1].scrollPosition=0;
	}
	else if ((((blocks[1].lastTime.tv_sec*1000000)+blocks[1].lastTime.tv_usec)+500000) < 
		 ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
//	else if (blocks[1].lastTime < currentTime -1){
		setTrackInfoDirty(true);
	}

	if (trackInfoIsDirty() && getTrackInfoString(&trackInfoString) != NULL) {
		writeBlock(1,trackInfoString);
		delete trackInfoString;
		setTrackInfoDirty(false);  
	}

	if (menuIsDirty()==true){
		blocks[2].scrollPosition=0;
	}
	else if ((((blocks[2].lastTime.tv_sec*1000000)+blocks[2].lastTime.tv_usec)+500000) < 
		 ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
//	else {if (blocks[2].lastTime < currentTime -1){
		setMenuDirty(true);
	}


	if (menuIsDirty() && getMenuString(&menuString) != NULL) {
		std::cout <<"Contents of the menu string: " << menuString << std::endl;
		writeBlock(2,menuString);
		delete menuString;
		setMenuDirty(false);  
	}

	
	if (getErrorString(&errorString) != NULL) {
		writeBlock(3,errorString);
		delete errorString;
		setErrorString(NULL);
	}
}

void LCDDisplay::writeBlock(int block, char *inputString)
{
	char outputString[4][33];
	int tokenNumber=0;
	int blockLength = blocks[block].length;
	int inputStringLength = strlen(inputString);

	std::string inputData(inputString);
	
	std::cout << "writing block: " << block << std::endl;
	std::cout << "size of input string: " << inputStringLength << std::endl;
	
	unsigned char pos = ((unsigned char) 128) + blocks[block].start;
	//std::cout<< "size of pos: " << (int)pos <<std::endl;
	write(displayDevice, &displayOptionMode, 1);
	write(displayDevice, &pos, 1);
			
	int j=blocks[block].scrollPosition;
	int writeLength = (inputData.length() -j <  blocks[block].length) ? inputData.length()-j : blocks[block].length;
	std::cout << "write Length " << writeLength << std::endl;
	std::cout << "writing scroll string: " << inputData.substr(j, blocks[block].length).c_str() << std::endl;
	
	
	/*if (inputData.length() <= blocks[block].length){	
	  for (int i = inputData.length();i<blocks[block].length;i++)
	    {
	      inputData[i]=' ';
	      writeLength = i;
	    }
	    }*/
	std::cout << "[1] input Length  " << inputData.length() << std::endl;
	std::cout << "[2] block Length  " << blocks[block].length << std::endl;
	std::cout << "[3] write Length  " << writeLength << std::endl;
	std::cout << "[4] string Contents  " << inputData << std::endl;
	
	if (write(displayDevice, inputData.substr(j, blocks[block].length).c_str(), writeLength) == -1)
		perror("Write didn't work");
     	
	if (inputData.length() >= blocks[block].length || writeLength > blocks[block].length) {  	  
	  write(displayDevice, " ",1);
	  write(displayDevice, inputData.c_str(), blocks[block].length-writeLength-1);
	}

	if (inputData.length() > blocks[block].length){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	if ((((blocks[block].lastTime.tv_sec*1000000)+blocks[block].lastTime.tv_usec)+500000) < 
	    ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
		blocks[block].scrollPosition++;
		if (blocks[block].scrollPosition >= inputData.length()){
			blocks[block].scrollPosition = 0;
	      
		}
		gettimeofday(&blocks[block].lastTime, NULL);
	}
		
	}
}


