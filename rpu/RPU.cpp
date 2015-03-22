
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <queue>
#include <iostream>


#include <RPU.h>

RPU::RPU(void *(*audioThreadEntry)(void *), void *(*ioThreadEntry)(void *))
{
	char *ipaddr = NULL;
	std::vector<char *> *addresses = getIPAddress();
	for (std::vector<char *>::iterator it = addresses->begin(); it != addresses->end(); it++) {
		std::cout << "Found IP Address: " << *it << std::endl;

		if (strncmp("127", *it, 3) != 0 && ipaddr == NULL)
			ipaddr = *it;
		else
			delete *it;
	}
	delete addresses;
	eventQueue = new std::queue<Event *>();
	keypad = new KeypadDevice();	
	player = new AudioPlayer(ipaddr);
	delete ipaddr;
	state = LOGIN_PROMPT;

	/* Create threads */
	if (pthread_create(&audioThread, NULL, audioThreadEntry, player) != 0) {
		perror("Could not create audio thread");
	}

	if (pthread_create(&ioThread, NULL, ioThreadEntry, this) != 0) {
		perror("Could not create audio thread");
	}
	running = true;
}

RPU::~RPU()
{
	running = false;
	player->stop();
	pthread_join(ioThread, NULL);
	pthread_join(audioThread, NULL);
	delete player;
	delete keypad;

}

void RPU::tick()
{
	Event *evt = getEvent();
	if (evt != NULL) {
		switch (evt->getType()) {
		case KEYPAD_INPUT:
			switch (*(char *)evt->getArguments()) {
			case 'p':
				player->playpause();
				break;
			case 'r':
				player->rewind();
				break;
			case 'q':
				running = false;
				break;
			case 'w':
			case 's':
			case 'f':
			case 'c':
			case '1' ... '9':
				fprintf(stderr, "Input not handled yet\n");
				break;
			default:
				fprintf(stderr, "RPU::tick: Unknown input\n");
				break;
			}
			break;
		default:
			break;
		}
	}
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

std::vector<char *> *RPU::getIPAddress()
{
	struct ifaddrs *ifAddrs = NULL, *curAddr = NULL;
	void *tmpAddr = NULL;
	char *tmpStr = NULL;
	std::vector<char *> *toRet = new std::vector<char *>;

	getifaddrs(&ifAddrs);

	for (curAddr = ifAddrs; curAddr != NULL; curAddr = curAddr->ifa_next) {
		if (!curAddr->ifa_addr)
			continue;

		if (curAddr->ifa_addr->sa_family == AF_INET) {
			tmpAddr = &((struct sockaddr_in *)curAddr->ifa_addr)->sin_addr;
			tmpStr = new char[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddr, tmpStr, INET_ADDRSTRLEN);
			toRet->push_back(tmpStr);

		} else {
			continue;
		}
	}

	return toRet;
}


