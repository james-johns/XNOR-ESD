

#ifndef _KEYBOARD_DEVICE_H_
#define _KEYBOARD_DEVICE_H_

#include <InputDevice.h>

class KeyboardDevice : public InputDevice {
public:
	KeyboardDevice();
	~KeyboardDevice();

	char getKeyPressed();
	void update();
	bool isConnected() { return true; }

private:
	char lastKeyPressed;
};

#endif
