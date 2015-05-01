/*!
 * @file RPU.cpp
 * @author James Johns
 */
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
#include <KeypadDevice.h>
#include <KeyboardDevice.h>


/*! RPU::RPU(void *(*audioThreadEntry)(void *), void *(*ioThreadEntry)(void *))
 * @author James Johns
 * @brief RPU constructor
 *
 * @param[in] audioThreadEntry function pointer to auidio thread start point
 * @param[in] ioThreadEntry function pointer to io thread start point
 */
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
	player = new AudioPlayer(ipaddr);
	delete ipaddr;

	/* Create input device as a keypad. If this fails, default to keyboard instead */
	input = new KeypadDevice();
	if (input->isConnected() == false) { // if keypad is not connected, fallback to keyboard
		delete input;
		input = new KeyboardDevice();
	}
	state = LOGIN_PROMPT;

	/*! Event queue must be initialised before threads as they depend on sending events to RPU */
	eventQueue = new std::queue<Event *>();

	/* Create threads */
	if (pthread_create(&audioThread, NULL, audioThreadEntry, player) != 0) {
		perror("Could not create audio thread");
	}

	if (pthread_create(&ioThread, NULL, ioThreadEntry, this) != 0) {
		perror("Could not create audio thread");
	}
	running = true;
}

/*! RPU::~RPU()
 * @author James Johns
 * @brief RPU destructor
 *
 */
RPU::~RPU()
{
	running = false;
	player->stop();
	pthread_join(ioThread, NULL);
	pthread_join(audioThread, NULL);
	delete player;
	delete input;

}

/*! RPU::tick()
 * @author James Johns
 * @brief RPU update tick
 *
 * Call iteratively to allow RPU to execute next action.
 * Handles events sent to the RPU, such as input, stream requests etc.
 */
void RPU::tick()
{
	Event *evt;
	while ((evt = getEvent()) != NULL) {
		switch (evt->getType()) {
		case Event::KEYPAD_INPUT:
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
			case 'w':/*!< Up key */
			case 's':/*!< Down key */
			case 'f':/*!< Enter key */
			case 'c':/*!< Cancel key */
			case '1' ... '9':
				fprintf(stderr, "Input not handled yet\n");
				break;
			default:
				fprintf(stderr, "RPU::tick: Unknown input\n");
				break;
			}
			break;
		case Event::QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

/*! RPU::sendEvent(Event *evt)
 * @author James Johns
 * @brief Send Event to RPU
 *
 * @param[in] evt Event to place in event queue
 */
void RPU::sendEvent(Event *evt)
{
	eventQueue->push(evt);
}

/*! RPU::getEvent()
 * @author James Johns
 * @brief Get event in event queue
 *
 * @return Event at front of event queue. Returns NULL if queue is empty.
 */
Event *RPU::getEvent()
{
	Event *evt = NULL;
	if (!eventQueue->empty()) {
		evt = eventQueue->front();
		eventQueue->pop();
	}
	return evt;
}

/*! RPU::getIPAddress()
 * @author James Johns
 * @brief Find the device's current IP address
 *
 * @return List of strings containing IP addresses that the device is associated with
 */
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


