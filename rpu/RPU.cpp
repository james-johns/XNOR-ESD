
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

AudioPlayer *RPU::getAudioPlayer()
{
	return player;
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


