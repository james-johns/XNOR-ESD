

#include <stdlib.h>

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
			return;
		}
	}
	std::cout << "file opened\n";

	displayOptionMode = (char) 254;
	displayClear = (char) 1;

	tcgetattr(displayDevice, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	tcsetattr(displayDevice, TCSANOW, &options);

	//display will enter option mode and wait for the next sspecial character.
	write(displayDevice, &displayOptionMode, 1);
	//special command to clear the display screen
	write(displayDevice, &displayClear, 1);

	blocks = (struct displayBlock *) malloc(sizeof(struct displayBlock)*4);
	blocks[0].start = 0;	blocks[0].length = 1;
	blocks[1].start = 1;	blocks[1].length = 15;
	blocks[2].start = 16;	blocks[2].length = 16;
	blocks[3].start = 0;	blocks[3].length = 32;
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

	char trackOutputString [4][16];
	char menuOutputString [4][17];
	char errorOutputString [4][33];
	int tokenNumber;

	for (int i=0;i>4;i++) {
		trackOutputString[i][0]=0;
		menuOutputString[i][0]=0;
		errorOutputString[i][0]=0;
	}

	if (playbackDirty == true & playbackString != NULL) {
		std::cout << "writing playback String\n";
		write(displayDevice, &displayOptionMode, 1);
		write(displayDevice, blockNumber1, sizeof(blockNumber1));
		write(displayDevice, playbackString, 1);
		playbackDirty = false;
      	}

	if (trackInfoDirty == true & trackInfoString != NULL) {
		tokenNumber=0;
		std::cout << "writing track Info String\n";
		std::cout <<"size of the trackinfo string: " << strlen(trackInfoString) << "\n";
		int tokenSize = strlen(trackInfoString);
      
		for (int i = 0; i < tokenSize; i += 15) {
			int tokenLength = (((tokenSize - i) >= 15) ? 15 : (tokenSize - i));
			strncpy(trackOutputString[i/15], trackInfoString + i, tokenLength);
			trackOutputString[i/15][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << "\n";
			tokenNumber++;
		}

		if(strlen(trackOutputString[tokenNumber-1]) <15) {
			for (int l=strlen(trackOutputString[tokenNumber-1]);l<15;l++) {
				trackOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (trackOutputString[k][0] != 0) {
				std:: cout << " string contents: " << trackOutputString[k] <<"\n";
				write(displayDevice, &displayOptionMode, 1);
				write(displayDevice, blockNumber2, sizeof(blockNumber2));
				write(displayDevice, trackOutputString[k], strlen(trackOutputString[k]));
				sleep(5);
			}
		}
		trackInfoDirty = false;  
	}

	if (menuDirty == true & menuString != NULL) {
		tokenNumber=0;
		std::cout << "writing track Info String\n";
		std::cout <<"size of the trackinfo string: " << strlen(menuString) << "\n";
		int tokenSize = strlen(menuString);

		for (int i = 0; i < tokenSize; i += 16) {
			int tokenLength = (((tokenSize - i) >= 16) ? 16 : (tokenSize - i));
			strncpy(menuOutputString[i/16], menuString + i, tokenLength);
			menuOutputString[i/16][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << "\n";
			tokenNumber++;
		}

		if(strlen(menuOutputString[tokenNumber-1]) <16) {
			for (int l=strlen(menuOutputString[tokenNumber-1]);l<16;l++) {
				menuOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (menuOutputString[k][0] != 0) {
				std:: cout << " string contents: " << menuOutputString[k] <<"\n";
				write(displayDevice, &displayOptionMode, 1);
				write(displayDevice, blockNumber3, sizeof(blockNumber3));
				write(displayDevice, menuOutputString[k], strlen(menuOutputString[k]));
				sleep(5);
			}
		}
		menuDirty = false;  
	}

	if (errorString != NULL) {
		tokenNumber=0;
		std::cout << "writing track Info String\n";
		std::cout <<"size of the trackinfo string: " << strlen(errorString) << "\n";
		int tokenSize = strlen(errorString);

		for (int i = 0; i < tokenSize; i += 32) {
			int tokenLength = (((tokenSize - i) >= 32) ? 32 : (tokenSize - i));
			strncpy(errorOutputString[i/32], errorString + i, tokenLength);
			errorOutputString[i/32][tokenLength] = '\0';
			std::cout << "tokenNumber: " << tokenNumber << "\n";
			tokenNumber++;
		}

		if(strlen(errorOutputString[tokenNumber-1]) <32) {
			for (int l=strlen(errorOutputString[tokenNumber-1]);l<32;l++) {
				errorOutputString[tokenNumber-1][l] = ' ';
			}
		}

		for(int k=0;k<tokenNumber;k++) {
			if (errorOutputString[k][0] != 0) {
				std:: cout << " string contents: " << errorOutputString[k] <<"\n";
				write(displayDevice, &displayOptionMode, 1);
				write(displayDevice, blockNumber1, sizeof(blockNumber1));
				write(displayDevice, errorOutputString[k], strlen(errorOutputString[k]));
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

