

#ifndef _KEYPAD_DEVICE_H_
#define _KEYPAD_DEVICE_H_

#include <string>
#include <iostream>
#include <sstream>

#include <string.h> //(legacy)
#include <stdio.h>
#include <unistd.h>
#include <libusb.h>

class KeypadDevice {
public:
	KeypadDevice();
	~KeypadDevice();

	//Setters for sevenSegData
	void set7Seg(const char * input);
	void set7Seg(std::string input);
	void set7Seg(unsigned int value);
	void set7Seg(char value, int digit);

	char getKeyPressed(void);

	void update(void);



private:
	libusb_device_handle *handle;

	std::string sevenSegData; //Characters to display on 7seg

	char keyPressed;  //The character which corresponds to the pressed key
	bool stillPressed; //Whether the key is still pressed (used for debouncing)
	int pressedColumn;

	unsigned int keysPressed; // bit pattern representing keys pressed

	char sendCommand(std::string command);

	//These functions convert input into hex codes for the 7 seg
	void charToSeg(char input, char output[2]);
	void stringToSeg(const char * input, char output[4][2]);

	//Returns the character of the keypad key selected by the parameters
	char keypadLookup(int row, int column);

	//Sets up port directions and resets device
	void configureDevice(void);
};


#endif
