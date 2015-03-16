
#include <KeypadDevice.h>

KeypadDevice::KeypadDevice()
{
	keyPressed = 0;
	set7Seg("");

	//These are the id numbers which identify the PIO converter
	const int vendorId = 0x09ca;
	const int productId = 0x5544;

	libusb_device **deviceList;
	libusb_device *found = NULL;

	ssize_t i = 0;
	int err = 0;

	struct libusb_device_descriptor desc;

	//Populate list of usb devices
	ssize_t count = libusb_get_device_list(NULL, &deviceList);

	if (count < 0) {
		perror("No devices found");
		return;
	}

	for (i = 0; i < count; i++) {
		libusb_device *device = deviceList[i];
		libusb_get_device_descriptor(device, &desc);
		if(desc.idVendor == vendorId && desc.idProduct == productId) { //if this is the device we want...
			found = device;
			break;
		}
	}

	if (found) {
		err = libusb_open(found, &handle);
		if (err) {
			perror("KeypadDevice");
			handle = NULL;
			return;
		}
	}
	else {
		printf("No devices found\n");
		handle = NULL;
		return;
	}

	libusb_free_device_list(deviceList, 1);

	libusb_detach_kernel_driver(handle, 0);
	libusb_detach_kernel_driver(handle, 1);
	libusb_claim_interface(handle, 0);
	libusb_claim_interface(handle, 1);

	//Set port directions
	configureDevice();
}

KeypadDevice::~KeypadDevice()
{
	if (handle != NULL) {
		libusb_release_interface(handle, 0);
		libusb_release_interface(handle, 1);
		libusb_attach_kernel_driver(handle, 0);
		libusb_attach_kernel_driver(handle, 1);
		libusb_close(handle);
	}
}

//Converts the specified char into the hex code for the 7 seg
void KeypadDevice::charToSeg(char input, char output[2])
{
	const int lookupSize = 18;

	char lookup[lookupSize][3] = {"3F","06","5B","4F","66","6D","7D","07","7F","6F","77","7C","39","5E","79","71","00", "80"};
						        // 0     1    2    3   4    5    6    7    8    9    A    B    C    D    E    F   ' '   .

	if(input == '.') {
		input = lookupSize-1; //'.' is the final entry in the array
	}
	else if(input == ' ') {
		input = lookupSize-2; //' ' is penultimate entry
	}
	else if(input >= '0' && input <= '9') {
		input -= '0'; //Get offset from 0 character
	}
	else if(input >= 'A' && input <= 'F') {
		input -= 'A'; //Get offset from A character (numbers and letters are not contiguous)
		input += 10; //Continue lookup after 9
	}
	else{
		output[0] = '0';
		output[1] = '0';
		return;
	}

	output[0] = lookup[input][0];
	output[1] = lookup[input][1];
}

//Convert a string to a 2d array of 7 seg hex codes
//Strings less than 4 characters are printed right justified
void KeypadDevice::stringToSeg(const char * input, char output[4][2])
{
	int i;
	int offset = 4 - strlen(input); //Shifts digits right to right justify

	for(i = 0; i < 4; i++){
		output[i][0] = '0';
		output[i][1] = '0';
	}

	for(i = 0; i < strlen(input); i++) {
		charToSeg(input[i], output[i + offset]);
	}
}

void KeypadDevice::set7Seg(const char * input)
{
	sevenSegData = input;
}

void KeypadDevice::set7Seg(std::string input)
{
	set7Seg(input.c_str());
}

void KeypadDevice::set7Seg(unsigned int value)
{
	std::ostringstream s; //Convert int to string
	s << value;

	sevenSegData = s.str();
}

void KeypadDevice::set7Seg(char value, int digit)
{
	if(digit >= 0 && digit < 4) {
		sevenSegData[digit] = value;
		std::cout << sevenSegData;
	}
}

//Returns the char value of the specified row/column on the keypad
char KeypadDevice::keypadLookup(int row, int column) {
	const char lookup [4][4] = {{'1','4','7','r'}, {'2','5','8','p'}, {'3', '6', '9', 'f'}, {'c', 'q', 'w', 's'}};

	return lookup[column][row];
}


//Send the specified command to the keypad
char KeypadDevice::sendCommand(std::string cmd)
{
	bool isRead = false;

	int result;
	int length;

	const int max = 8;

	unsigned char buffer[max]; //Stores data read from keypad
	unsigned char temp[2]; //Stores characters from read data

	if(cmd.length() > max) {
		fprintf(stderr, "Command too long\n");
		return -1;
	}

	result = libusb_bulk_transfer(handle, 1, (unsigned char *) cmd.c_str(), cmd.length(), &length, 0);

	if(result != 0 || length != cmd.length()) {
		printf("Problem!\n");
		//error();
		return -1;
	}

	//Get result returned from keypad
	result = libusb_bulk_transfer(handle, 0x82, buffer, 8, &length, 0);
	if(result) { //Error
		return -1;
	}

	//Get return value from buffer
	for(int i = 0; i < length; i++) {
		if(buffer[i] == 'F') { //This means it's returning read data
			isRead = true;
		}
	}
	if(isRead) {
		return buffer[4]; //This is the char of returned data following 'F'
	}
	else {
		return 0;
	}
}

//Retrieves and clears key press (allowing another press to be registered)
//Modify to be blocking?
char KeypadDevice::getKeyPressed()
{
	char temp = keyPressed;
	keyPressed = 0;
	return temp;
}




//Refresh 7 segs and scan keypad
void KeypadDevice::update()
{
	int i, result, row;

	char readChar, pressedChar;

	char hexCodes[4][2];
	char data[2];

	std::string commandRead = "@00P1?\r";
	std::string commandWrite = "@00P200\r";
	std::string commandSelect = "@00P000\r";

	stringToSeg(sevenSegData.c_str(), hexCodes);

	for(i = 0; i < 4; i++) { //For each 7 seg...

		//Get hex code for current 7 seg
		data[0] = hexCodes[i][0];
		data[1] = hexCodes[i][1];

		//Clear 7 seg before selecting the next one (makes for a cleaner display)
		commandWrite[5] = '0';
		commandWrite[6] = '0';
		sendCommand(commandWrite);

		//Select appropriate 7 seg
		commandSelect[6] = '0' + (1 << i);
		sendCommand(commandSelect);

		//Write number to display
		commandWrite[5] = data[0]; //Get hex chars from array
		commandWrite[6] = data[1];
		sendCommand(commandWrite);

		usleep(2000); //Need to calculate delay from desired refresh rate

		//Read from keypad
		readChar = sendCommand(commandRead);
		if(readChar > '0' && !stillPressed) { //If a button has been pressed...
			row = (readChar - '0'); //Get row of pressed button

			row /= 2; //Convert 1,2,4,8 to the row number (0,1,2,3)
			if(row == 4) {
				row--;
			}

			//Use row and column to get the value of the pressed key
			keyPressed = keypadLookup(row,i);
			pressedColumn = i;
			stillPressed = true;
		}
		else if(readChar == '0' && pressedColumn == i && stillPressed) { //If button has been released...
			pressedChar = 0; //Reset pressed char to allow another key press
			stillPressed = false;
		}
	}
}

void KeypadDevice::configureDevice()
{
	std::string configZero = "@00D000\r"; //Set port 0 as output
	std::string configOne = "@00D1FF\r"; //Set port 1 as input
	std::string configTwo = "@00D200\r"; //Set port 2 as output

    int i, len, result;

    result = libusb_reset_device(handle);
    if (result < 0) {
        fprintf(stderr, "Unable to reset device\n");
        return;
    }

	sendCommand(configZero);
	sendCommand(configOne);
	sendCommand(configTwo);
}
