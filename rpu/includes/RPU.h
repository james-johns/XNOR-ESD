

#ifndef _RPU_H_
#define _RPU_H_

#include <pthread.h>
#include <queue>

#include <Event.h>
#include <KeypadDevice.h>
#include <AudioPlayer.h>

enum RPUState_e {
	LOGIN_PROMPT, 
	DISPLAY_MENU, 
	SELECT_LANGUAGE, 
	SELECT_KNOWLEDGE,
	REQUEST_STREAM
};

class RPU {
public:
	RPU(void *(*audioThreadEntry)(void *), void *(*ioThreadEntry)(void *));
	~RPU();
	
	void tick(); // handle events and manage other objects

	void sendEvent(Event *evt);
	Event *getEvent();

	KeypadDevice *getKeypadDevice() { return keypad; }

	bool isRunning() { return running; }

	static std::vector<char *> *getIPAddress();

private:
	bool running;
	enum RPUState_e state;
	std::queue<Event *> *eventQueue;
	KeypadDevice *keypad;
	AudioPlayer *player;
	pthread_t audioThread, ioThread;
};

#endif
