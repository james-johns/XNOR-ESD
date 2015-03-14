
#include <stdio.h>
#include <pthread.h>
#include <queue>

#include <RPU.h>

RPU::RPU(void *(*audioThreadEntry)(void *), void *(*ioThreadEntry)(void *))
{
	eventQueue = new std::queue<Event *>();
	keypad = new KeypadDevice();	
	player = new AudioPlayer();
	state = LOGIN_PROMPT;

	/* Create threads */
	if (pthread_create(&audioThread, NULL, audioThreadEntry, player) != 0) {
		perror("Could not create audio thread");
	}

	if (pthread_create(&ioThread, NULL, ioThreadEntry, this) != 0) {
		perror("Could not create audio thread");
	}
}

RPU::~RPU()
{
	player->stop();
	pthread_join(ioThread, NULL);
	pthread_join(audioThread, NULL);
	delete player;
	delete keypad;

}

void RPU::sendEvent(Event *evt)
{
	eventQueue->push(evt);
}

Event *RPU::getEvent()
{
	Event *evt = NULL;
	if (!eventQueue->empty()) {
		evt = eventQueue->front();
		eventQueue->pop();
	}
	return evt;
}


