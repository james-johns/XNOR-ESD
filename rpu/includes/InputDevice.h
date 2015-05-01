

#ifndef _INPUT_DEVICE_H_
#define _INPUT_DEVICE_H_


class InputDevice {
public:

	virtual char getKeyPressed(void) {}
	virtual void update() {}
	virtual bool isConnected() {}

};


#endif
