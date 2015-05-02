

#ifndef _INPUT_DEVICE_H_
#define _INPUT_DEVICE_H_


class InputDevice {
public:

	virtual char getKeyPressed(void) = 0;
	virtual void update() = 0;
	virtual bool isConnected() = 0;

};


#endif
