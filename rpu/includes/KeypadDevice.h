

#ifndef _KEYPAD_DEVICE_H_
#define _KEYPAD_DEVICE_H_

#include <libusb.h>

class KeypadDevice {
public:
	KeypadDevice();
	~KeypadDevice();

	void set7Seg(unsigned short value);
	unsigned int getKeysPressed();

	void update();

private:
	int writeCommand(char * command, libusb_device_handle *handle);
	int readPort(libusb_device_handle *handle);

	libusb_device_handle *handle;
	short sevenSegValue; // hex value to display on 7seg
	unsigned int keysPressed; // bit pattern representing keys pressed
};


#endif
