//set up librarys
#include <stdlib.h>
#include <stdexcept>
#include <LCDDisplay.h>
#include <sys/time.h>

LCDDisplay::LCDDisplay() : Display()
{	struct termios options;
	displayOptionMode = (unsigned char) 254;
	displayClear = (char) 1;
       

	std::cout << "opening ttyUSB0\n";
	displayDevice = open("/dev/ttyUSB0", O_RDWR) ;//open the tty file of the first USB port
	if( displayDevice == -1) {//if unable to open the file:
		std::cout << "Cannot open USB device on /dev/ttyusb0\n\n";
		displayDevice = open("/dev/ttyUSB1", O_RDWR) ;
		if( displayDevice == -1) {//if unable to open the device with the 2nd USB port
			std::cout <<  "Cannot open USB device on /dev/ttyusb1\n\n";
		}
	}
	std::cout << "file opened\n";
	
	
	tcgetattr(displayDevice, &options);//get attributes of the displayDevice
	cfsetispeed(&options, B9600);//set the input baud rate to 9600
	cfsetospeed(&options, B9600);//set the output baud rate to 9
	tcsetattr(displayDevice, TCSANOW, &options);//save the atrributes to the device

	blocks = (struct displayBlock *) malloc(sizeof(struct displayBlock)*4);//struct for dealing with strings
	//contains the starting position of the string on the display
	blocks[0].start = 0;	blocks[0].length = 1; 
        //starting position when scrolling and the last time the function was called
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
	close(displayDevice);//close the device when finished
}

bool LCDDisplay::isConnected()
{
	return (displayDevice != -1);//if the constructor fails is connected is set to false
}

void LCDDisplay::refresh()
{
	char blockNumber1[1]={128};//first character of the display
	char playbackOutputString[1]={0};//initialise the playback output string as NULL
	char playIcon[1]={62}; //ASCII value of closest symbol to play icon
	char pauseIcon[1]={4}; //ASCII value of closest symbol to pause icon
	char rewindIcon[1]={127}; //ASCII value of closest symbol to rewind icon
	char fForwardIcon[1]={126}; //ASCII value of closest symbol to fast forward icon
	char *playbackString; //char pointer for the playback String
	char *trackInfoString; //char pointer for the track Info String
	char *menuString; //char pointer for the menu String
	char *errorString; //char pointer for the error String
	
	struct timeval currentTime; // contains the struct needed for gettimeofday to function

	gettimeofday(&currentTime,NULL);//saves the current time in seconds that refresh was called
	//if the last time the function ran is half a second more than the current time:
	if ((((blocks[0].lastTime.tv_sec*1000000)+blocks[0].lastTime.tv_usec)+500000) < 
	    ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
		setPlaybackDirty(true); // set the playback dirty flag

	}
	//if the playback region is dirty and the string does not contain a NULL:
	if (playbackIsDirty() && getPlaybackString(&playbackString) != NULL) {
		std::cout << "playback Button Pressed\n";
		int tokenSize = strlen(playbackString);
      		//Based on the letter passed by the playback String enter a following case:
		switch(*playbackString){
		case 'p':
                        //copy the ASCII value into the playback output String
			strncpy(playbackOutputString,playIcon,8);
			break;
		case 'w':
			//copy the ASCII value into the playback output String
			strncpy(playbackOutputString,pauseIcon,8);
			break;
		case 'f':
			//copy the ASCII value into the playback output String
			strncpy(playbackOutputString,fForwardIcon,8);
			break;
		case 'r':
			//copy the ASCII value into the playback output String
			strncpy(playbackOutputString,rewindIcon,8);
			break;
		}
		
		write(displayDevice, &displayOptionMode, 1);//enter the option mode for the device
		write(displayDevice, &blockNumber1, 1);//set the device to begin writing to block 1
		//write the currrent contents of the playback string to the display
		write(displayDevice, playbackOutputString, 1);
		delete playbackString; //delete the contents of the playback String
		setPlaybackDirty(false); //set the playback region flag to clean
	}
	//if the track info region is dirty:
	if (trackInfoIsDirty()==true){
		blocks[1].scrollPosition=0;//set the scroll position to the first character of the region
	}
	//if the region is not dirty wait until half a second has passed and make the region dirty.
	else if ((((blocks[1].lastTime.tv_sec*1000000)+blocks[1].lastTime.tv_usec)+500000) < 
		 ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
		setTrackInfoDirty(true);//Set the region flag to dirty
	}
	// if the track info region is dirty and the track info string does not contain NULL :
	if (trackInfoIsDirty() && getTrackInfoString(&trackInfoString) != NULL) {
		//call the write block function passing the track info string and the block number 1
		writeBlock(1,trackInfoString); 
		delete trackInfoString; // delete the track info string
		setTrackInfoDirty(false);  // set the track info region flag to clean
	}
	//if the menu region is dirty
	if (menuIsDirty()==true){
		blocks[2].scrollPosition=0;//set the scroll position to 0
	}
	//if the region is not dirty wait until half a second has passed and make the region dirty
	else if ((((blocks[2].lastTime.tv_sec*1000000)+blocks[2].lastTime.tv_usec)+500000) < 
		 ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
		setMenuDirty(true);//Set the region flag to dirty
	}

	//if the menu region is dirt and the menuString doesnt contain NULL
	if (menuIsDirty() && getMenuString(&menuString) != NULL) {
		//call the write block function passing the menu string and the block number 2
		writeBlock(2,menuString);
		delete menuString;//delete the menu String
		setMenuDirty(false);  // set the menu region flag to clean
	}

	// if the error String is not NULL :
	if (getErrorString(&errorString) != NULL) {
		//call the write block function passing the Error string and the block number 3
		writeBlock(3,errorString);
		delete errorString; // delete the error String
		setErrorString(NULL); // set the Error String to NULL
	}
}

void LCDDisplay::writeBlock(int block, char *inputString)
{
	
	std::string inputData(inputString);//convert char * array to a string
	
	std::cout << "writing block: " << block << std::endl;//debugging string
	std::cout << "size of input string: " << inputData.length() << std::endl;//debugging string
	
	unsigned char pos = ((unsigned char) 128) + blocks[block].start;//set the starting position of the string
	//std::cout<< "size of pos: " << (int)pos <<std::endl; //debugging string
	write(displayDevice, &displayOptionMode, 1);//set the display to  option mode
	write(displayDevice, &pos, 1); //set the starting position of the string
			
	int j=blocks[block].scrollPosition; // set j to be the current scroll position
	//the length of the string - the region size and sets it to block length if shorter than the region size
	int writeLength = (inputData.length() -j <  blocks[block].length) ? inputData.length()-j : blocks[block].length;
	std::cout << "write Length " << writeLength << std::endl;//debugging string
        //debugging string
	std::cout << "writing scroll string: " << inputData.substr(j, blocks[block].length).c_str() << std::endl;
	
	//if the length of the string is less than the region length:
	if (inputData.length() <= blocks[block].length){
		//for each additional character until reaching the region length
		for (int i = inputData.length();i<blocks[block].length;i++)
		{
			inputData.push_back(' ') ; // set the current character to a space
			writeLength = i; //debugging string
		}
	}
	std::cout << "[1] input Length  " << inputData.length() << std::endl;//debugging string
	std::cout << "[2] block Length  " << blocks[block].length << std::endl;//debugging string
	std::cout << "[3] write Length  " << writeLength << std::endl;//debugging string
	std::cout << "[4] string Contents  " << inputData << std::endl;//debugging string
	
	//write the string to the device again allowing scrolling (IS THIS NEEDED ?)
	if (write(displayDevice, inputData.substr(j, blocks[block].length).c_str(), writeLength) == -1)
		perror("Write didn't work");//return an error if the write fails
     	
	//if the length of input Data is longer than region length or the writelength is longer than the region:
	if (inputData.length() >= blocks[block].length || writeLength > blocks[block].length) {  	  
		write(displayDevice, " ",1);//append a space after the last character in the string
		write(displayDevice, inputData.c_str(), blocks[block].length-writeLength-1);//write to the display
	}
	//if the langth of the string is greater than the region length:
	if (inputData.length() > blocks[block].length){
		struct timeval currentTime; // set up time struct
		gettimeofday(&currentTime, NULL);//get the current time of day
		//if half a second has passed since the function was last called :
		if ((((blocks[block].lastTime.tv_sec*1000000)+blocks[block].lastTime.tv_usec)+500000) < 
		    ((currentTime.tv_sec*1000000)+currentTime.tv_usec)) {
			blocks[block].scrollPosition++;	//increment the scroll position
			//if the scroll position is more than the input length
			if (blocks[block].scrollPosition >= inputData.length()){
				blocks[block].scrollPosition = 0;//set the scroll position to 0
	      
			}
			gettimeofday(&blocks[block].lastTime, NULL);// save the currrent time 
		}
		
	}
}


