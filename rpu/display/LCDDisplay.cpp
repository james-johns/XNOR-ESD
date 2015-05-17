#include <stdlib.h>
#include <stdexcept>
#include <LCDDisplay.h>

LCDDisplay::LCDDisplay() : Display()
{
	struct termios options;
	std::cout << "opening ttyUSB0\n";
	displayDevice = open("/dev/ttyUSB0", O_RDWR) ;
	if( displayDevice == -1) {
		std::cout << "Cannot open USB device on /dev/ttyusb0\n\n";
		displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
		if( displayDevice == -1) {
			std::cout <<  "Cannot open USB device on /dev/ttyusb1\n\n";
			bool isConnected = false;	
			//	throw std::invalid_argument( "Display Device not detected" );
		}
	}
	std::cout << "file opened\n";

	displayOptionMode = (char) 254;
	displayClear = (char) 1;
	
	tcgetattr(displayDevice, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	tcsetattr(displayDevice, TCSANOW, &options);

	blocks = (struct displayBlock *) malloc(sizeof(struct displayBlock)*4);
	blocks[0].start = 0;	blocks[0].length = 1;
	blocks[1].start = 1;	blocks[1].length = 15;
	blocks[2].start = 64;	blocks[2].length = 16;
	blocks[3].start = 0;	blocks[3].length = 32;

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


	if (trackInfoIsDirty() && getTrackInfoString(&trackInfoString) != NULL) {
		writeBlock(1,trackInfoString);
		delete trackInfoString;
		setTrackInfoDirty(false);  
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

	std::cout << "writing block: " << block << std::endl;
	std::cout << "size of input string: " << inputStringLength << std::endl;
	
	for (int i = 0; i < inputStringLength; i += blocks[block].length) {
		int tokenLength = (((inputStringLength - i) >= blockLength) ? blockLength : (inputStringLength - i));

		strncpy(outputString[i/blockLength], inputString + i, tokenLength);
		outputString[i/blockLength][tokenLength] = '\0'; // null terminate after the data we copied

		//	std::cout << "tokenNumber: " << tokenNumber << "\n";
		std::cout << "writing string: " << outputString[tokenNumber] << std::endl;
		tokenNumber++;
	}
	
	int lastTokenLength = strlen(outputString[tokenNumber - 1]);
	if(lastTokenLength < blockLength) {
		for (int i = lastTokenLength; i < blockLength; i++) {
			outputString[tokenNumber - 1][i] = ' ';
		}
		outputString[tokenNumber - 1][blockLength] = '\0'; // ensure the output string is null terminated
	}
	
	for(int i=0; i < tokenNumber; i++) {
		if (outputString[i][0] != 0) {
			char pos = ((char) 128) + blocks[block].start;
			write(displayDevice, &displayOptionMode, 1);
			write(displayDevice, &pos, 1);
			write(displayDevice, outputString[i], strlen(outputString[i]));
			sleep(5);
		}
	}
}


