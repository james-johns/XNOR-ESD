

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
			printf( "Cannot open USB device on /dev/ttyusb1\n\n");
				
			throw std::invalid_argument( "Display Device not detected" );
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
	blocks[2].start = 16;	blocks[2].length = 16;
	blocks[3].start = 0;	blocks[3].length = 32;

	//display will enter option mode and wait for the next special character.
	write(displayDevice, &displayOptionMode, sizeof(displayOptionMode));
	//special command to clear the display screen
	write(displayDevice, &displayClear, sizeof(displayClear));
	std::cout << "clearing display" << std::endl;
}

LCDDisplay::~LCDDisplay()
{
	close(displayDevice);
}

void LCDDisplay::refresh()
{
	int currentChar;
	char blockNumber1[1]={128};//first character of the display
	char blockNumber2[1]={129};//2nd character of the display
	char blockNumber3[1]={192};//10th character of the display
	char displayOptionMode[1] = {254};
	char displayClear[1] = {1};
	char trackOutputString [4][16];
	char menuOutputString [4][17];
	char errorOutputString [1][33];
	char playbackOutputString[1];
	int tokenNumber;

	char playIcon[1]={62};
	char pauseIcon[1]={219};
	char rewindIcon[1]={127};
	char fForwardIcon[1]={126};

	for (int i=0;i>4;i++) {
		playbackOutputString[0]=0;
		trackOutputString[i][0]=0;
		menuOutputString[i][0]=0;
		errorOutputString[i][0]=0;
	}

	if (playbackDirty == true & playbackString != NULL) {
		tokenNumber=0;
		std::cout << "playback Button Pressed\n";
		int tokenSize = strlen(playbackString);
      		
		switch(*playbackString){
		case 'p':
		
			strncpy(playbackOutputString,playIcon,8);
			std::cout << "play symbol" <<  std::endl;
			break;
		case 'w':
			strncpy(playbackOutputString,pauseIcon,8);
			std::cout << "Rewind symbol" <<  std::endl;
			break;
		case 'f':
			strncpy(playbackOutputString,fForwardIcon,8);
			std::cout << "Fastforward symbol" <<  std::endl;
			break;
		case 'r':
			strncpy(playbackOutputString,rewindIcon,8);
			std::cout << "Pause symbol" << std::endl;
			break;
		}

		write(displayDevice, displayOptionMode, 1);
		write(displayDevice, blockNumber1, sizeof(blockNumber1));
		write(displayDevice, playbackOutputString, 1);
		playbackDirty = false;
	}

	if (trackInfoDirty == true & trackInfoString != NULL) {
		tokenNumber=0;
		std::cout << "Playing Track\n";
		int tokenSize = strlen(trackInfoString);
      		std::cout <<"size of the trackinfo string: " << tokenSize << std::endl;

		for (int i = 0; i < tokenSize; i += 15) {
			int tokenLength = (((tokenSize - i) >= 15) ? 15 : (tokenSize - i));
			strncpy(trackOutputString[i/15], trackInfoString + i, tokenLength);
			trackOutputString[i/15][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << std::endl;
			tokenNumber++;
		}

		if(strlen(trackOutputString[tokenNumber-1]) <15) {
			for (int l=strlen(trackOutputString[tokenNumber-1]);l<15;l++) {
				trackOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (trackOutputString[k][0] != 0) {
				std:: cout << " string contents: " << trackOutputString[k] <<std::endl;
				write(displayDevice, displayOptionMode, 1);
				write(displayDevice, blockNumber2, sizeof(blockNumber2));
				write(displayDevice, trackOutputString[k], 15);
				sleep(5);
			}
		}
		trackInfoDirty = false;  
	}

	if (menuDirty == true & menuString != NULL) {
		tokenNumber=0;
		std::cout << "Scroll button detected\n";
		int tokenSize = strlen(menuString);
		std::cout <<"size of the menu string: " << tokenSize << std::endl;

		for (int i = 0; i < tokenSize; i += 16) {
			int tokenLength = (((tokenSize - i) >= 16) ? 16 : (tokenSize - i));
			strncpy(menuOutputString[i/16], menuString + i, tokenLength);
			menuOutputString[i/16][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << std::endl;
			tokenNumber++;
		}

		if(strlen(menuOutputString[tokenNumber-1]) <16) {
			for (int l=strlen(menuOutputString[tokenNumber-1]);l<=16;l++) {
				menuOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (menuOutputString[k][0] != 0) {
				std:: cout << " string contents: " << menuOutputString[k] <<std::endl;
				write(displayDevice, displayOptionMode, sizeof(displayOptionMode));
				write(displayDevice, blockNumber3, sizeof(blockNumber3));
				write(displayDevice, menuOutputString[k], 16);
				sleep(5);
			}
		}
		menuDirty = false;  
	}

	if (errorString != NULL) {
		tokenNumber=0;
		std::cout << "ERROR in Progress\n";
		int tokenSize = strlen(errorString);
		std::cout <<"size of the Error string: " << tokenSize << std::endl;
		//display will enter option mode and wait for the next special character.
		write(displayDevice, &displayOptionMode, 1);
		//special command to clear the display screen
		write(displayDevice, &displayClear, 1);
	
		for (int i = 0; i < tokenSize; i += 32) {
			int tokenLength = (((tokenSize - i) >= 32) ? 32 : (tokenSize - i));
			strncpy(errorOutputString[i/32], errorString + i, tokenLength);
			errorOutputString[i/32][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << std::endl;
			tokenNumber++;
		}

		if(strlen(errorOutputString[tokenNumber-1]) <32) {
			for (int l=strlen(errorOutputString[tokenNumber-1]);l<32;l++) {
				errorOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (errorOutputString[k][0] != 0) {
				std:: cout << " string contents: " << errorOutputString[k] <<std::endl;
				write(displayDevice, displayOptionMode, 1);
				write(displayDevice, blockNumber1, sizeof(blockNumber1));
				write(displayDevice, errorOutputString[k],32);
				sleep(5);
			}
		}
		errorString = NULL;
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

		std::cout << "tokenNumber: " << tokenNumber << "\n";
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
			std:: cout << " string contents: " << outputString[i] <<"\n";
			char pos = ((char) 128) + blocks[block].start;
			write(displayDevice, &displayOptionMode, 1);
			write(displayDevice, &pos, 1);
			write(displayDevice, outputString[i], strlen(outputString[i]));
			sleep(5);
		}
	}
}


