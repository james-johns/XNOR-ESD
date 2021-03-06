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
#include <NCursesDisplay.h>
#include <Menu.hpp>
#include <VLCAudioPlayer.h>
#include <CDDWebApi.h>

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
		if (strncmp("127", *it, 3) != 0 && ipaddr == NULL)
			ipaddr = *it;
		else
			delete *it;
	}
	delete addresses;
	printf("%s\n", ipaddr);
	player = new VLCAudioPlayer(ipaddr);
	cddapi = new CDDWebApi("10.0.0.2");
	delete ipaddr;


	mainMenu = new Menu();
	mainMenu->addMenuItem("Enter Exhibit");
	mainMenu->addMenuItem("Change Language");
	mainMenu->addMenuItem("Change Knowledge Level");

	/* Create input device as a keypad. If this fails, default to keyboard instead */
	input = new KeypadDevice();
	if (input->isConnected() == false) { // if keypad is not connected, fallback to keyboard
		delete input;
		input = new KeyboardDevice();
	}
	state = LOGIN_PROMPT;

	// connect to NCurses display by default
	display = new NCursesDisplay();
	display->setErrorString("Please enter PIN to unlock");

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
	delete display;
	delete cddapi;
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
	//Checks for incoming broadcast. Mutes regular streaming
	//Returns bool; true if broadcasting, false if not 
	player->listen(); 

	Event *evt = getEvent();
	do {
		if (evt != NULL) {
			if (evt->getType() == Event::QUIT) {
				running = false;
			}
		}
		switch (state) {
		case LOGIN_PROMPT:
			loginPrompt(evt);
			break;
		case DISPLAY_MENU:
			displayMenu(evt);
			break;
		case SELECT_LANGUAGE:
			selectLanguage(evt);
			break;
		case SELECT_KNOWLEDGE:
			selectKnowledge(evt);
			break;
		default:
			break;
		}
		
		if (evt != NULL)
			delete evt;
		evt = getEvent();
	} while (evt != NULL);
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

void RPU::loginPrompt(Event *evt)
{
	static bool entered = false;

	if (entered == false) {
		display->setErrorString("Please enter PIN to unlock");
		entered = true;
	}

	if (evt == NULL)
		return;

	switch (evt->getType()) {
	case Event::KEYPAD_INPUT:
		switch (*(char *)evt->getArguments()) {
		case 'q':
			running = false;
			break;
		case 'c':/*!< Enter key */
			/* enter selected menu entry */
			if (cddapi->login(numberInput.c_str()) == 0) {
				state = DISPLAY_MENU;
				display->setMenuString(mainMenu->getCurrentMenuItem());
				display->setErrorString(NULL);
				entered = false;
			} else {
				display->setErrorString(cddapi->getLastSentMessage().c_str());
			}
			break;
		case '1' ... '9':
			/* capture PIN input */
		        display->setErrorString("Please enter PIN to unlock");
			numberInput.push_back(*(char *)evt->getArguments());
			if (numberInput.length() > 4) // pop data from front of string to reduce to 4 character string
				numberInput.erase(0, numberInput.length() - 4);
			break;
		case 'p':/*!< play */
		case 'r':/*!< rewind */
		case 'f':/*!< Fast Forward */
		case 'w':/*!< Up key */
		case 's':/*!< Down key */
		default:
			/* ignored */
			break;
		}
		break;
	default:
		break;
	}
}

void RPU::displayMenu(Event *evt)
{
	static bool entered = false;

	if (entered == false) {
		display->setMenuString(mainMenu->getCurrentMenuItem());
		entered = true;
	}

	if (evt == NULL)
		return;
	
	switch (evt->getType()) {
	case Event::KEYPAD_INPUT:
		switch (*(char *)evt->getArguments()) {
		case 'p':
			if (player != NULL) {
				player->playpause();
				display->setPlaybackString(((player->isPlaying()) ? "Play" : "Pause"));
			}
			break;
		case 'r':
		  if (player != NULL) {
				player->rewind();
			}
			break;
		case 'f': /*!< Fast Forward */
		  if (player != NULL) {
		    player->fastForward();
		  }
			break;
		case 'q':
			state = LOGIN_PROMPT;
			display->setErrorString("Please enter PIN to unlock");
			display->setMenuString(NULL);
			display->setPlaybackString(NULL);
			display->setTrackInfoString(NULL);
			break;
		case 'w':/*!< Up key */
			mainMenu->up();
			display->setMenuString(mainMenu->getCurrentMenuItem());
			break;
		case 's':/*!< Down key */
			mainMenu->down();
			display->setMenuString(mainMenu->getCurrentMenuItem());
			break;
		case 'c':/*!< Enter (continue) key */
			/* Enter selected menu entry */
			if (mainMenu->getCurrentSelected() == 0) {
				display->setErrorString(numberInput.c_str());
				cddapi->requestAudioStream(numberInput.c_str());
				player->play();
			} else if (mainMenu->getCurrentSelected() == 1) {
				state = SELECT_LANGUAGE;
				entered = false;
			} else if (mainMenu->getCurrentSelected() == 2) {
				state = SELECT_KNOWLEDGE;
				entered = false;
			}
			break;
		case '1' ... '9':
			numberInput.push_back(*(char *)evt->getArguments());
			if (numberInput.length() > 4) // pop data from front of string to reduce to 4 character string
				numberInput.erase(0, numberInput.length() - 4);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void RPU::selectLanguage(Event *evt)
{
	static bool entered = false;
	static int language = 0;
	char *langString;
	int tmpLang = language;
	std::vector<std::string> supportedLanguages = cddapi->getSupportedLanguages();

	if (entered == false) {
		do {
			language++;
			langString = (char *) supportedLanguages[language].c_str();
		} while (langString == NULL && language < supportedLanguages.size());
		if (language >= supportedLanguages.size())
			language = tmpLang;
		display->setMenuString(supportedLanguages[language].c_str());
		entered = true;
	}

	if (evt == NULL)
		return;
	

	switch (evt->getType()) {
	case Event::KEYPAD_INPUT:
		switch (*(char *)evt->getArguments()) {
		case 'p':
			if (player != NULL) {
				player->playpause();
				display->setPlaybackString((char *)((player->isPlaying()) ? "Play" : "Pause"));
			}
			break;
		case 'r':
			if (player != NULL) {
				player->rewind();
			}
			break;
		case 'f': /*!< Fast Forward */
		  if (player != NULL) {
		    player->fastForward();
		  }
			break;
		case 'q':
			state = DISPLAY_MENU;
			entered = false;
			break;
		case 'w':/*!< Up key */
			do {
				language++;
				langString = (char *) supportedLanguages[language].c_str();
			} while (langString == NULL && language < supportedLanguages.size());
			if (language >= supportedLanguages.size())
				language = tmpLang;
			display->setMenuString(supportedLanguages[language].c_str());
			break;
		case 's':/*!< Down key */
			do {
				language--;
				langString = (char *) supportedLanguages[language].c_str();
			} while (langString == NULL && language > 0);
			if (language < 0)
				language = tmpLang;
			display->setMenuString(supportedLanguages[language].c_str());
			break;
		case 'c':/*!< Enter key */
			cddapi->changeLanguage(language);
			state = DISPLAY_MENU;
			entered = false;
			break;
		case '1' ... '9':
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void RPU::selectKnowledge(Event *evt)
{	
	static bool entered = false;
	static int knowledge = 0;
	char *knowString;
	int tmpKnow = knowledge;
	std::vector<std::string> supportedKnowledgeLevels = cddapi->getSupportedKnowledgeLevels();

	if (entered == false) {
		do {
			knowledge++;
			knowString = (char *) supportedKnowledgeLevels[knowledge].c_str();
		} while (knowString == NULL && knowledge < supportedKnowledgeLevels.size());
		if (knowledge >= supportedKnowledgeLevels.size())
			knowledge = tmpKnow;
		display->setMenuString(supportedKnowledgeLevels[knowledge].c_str());
		entered = true;
	}

	if (evt == NULL)
		return;
	

	switch (evt->getType()) {
	case Event::KEYPAD_INPUT:
		switch (*(char *)evt->getArguments()) {
		case 'p':
			if (player != NULL) {
				player->playpause();
				display->setPlaybackString((char *)((player->isPlaying()) ? "Play" : "Pause"));
			}
			break;
		case 'r':
			if (player != NULL) {
				player->rewind();
			}
			break;
		case 'f':/*!< Fast Forward */
		  if(player != NULL) {
		    player->fastForward();
		  }
			break;
		case 'q':
			state = DISPLAY_MENU;
			entered = false;
			break;
		case 'c':/*!< Enter key */
			cddapi->changeKnowledgeLevel(knowledge);
			state = DISPLAY_MENU;
			entered = false;
			break;
		case 'w':/*!< Up key */
			do {
				knowledge++;
				knowString = (char *) supportedKnowledgeLevels[knowledge].c_str();
			} while (knowString == NULL && knowledge < supportedKnowledgeLevels.size());
			if (knowledge >= supportedKnowledgeLevels.size())
				knowledge = tmpKnow;
			display->setMenuString(supportedKnowledgeLevels[knowledge].c_str());
			break;
		case 's':/*!< Down key */
			do {
				knowledge--;
				knowString = (char *) supportedKnowledgeLevels[knowledge].c_str();
			} while (knowString == NULL && knowledge >= 0);
			if (knowledge < 0)
				knowledge = tmpKnow;
			display->setMenuString(supportedKnowledgeLevels[knowledge].c_str());
			break;
		case '1' ... '9':
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void RPU::requestStream(Event *evt)
{
	switch (evt->getType()) {
	case Event::KEYPAD_INPUT:
		switch (*(char *)evt->getArguments()) {
		case 'p':
			if (player != NULL) {
				player->playpause();
				display->setPlaybackString((char *)((player->isPlaying()) ? "Play" : "Pause"));
			}
			break;
		case 'r':
			if (player != NULL) {
				player->rewind();
			}
			break;
		case 'f':/*!< Fast Forward */
		  if (player != NULL) {
		    player->fastForward();
		  }
			break;
		case 'q': /* cancel key - return to menu */
			state = DISPLAY_MENU;
			break;
		case 'c':/*!< Enter key */
			/* TODO: Request stream using last 4 digits input */
			break;
		case '1' ... '9':
			/* TODO: Capture Exhibit ID input */
			break;
		case 'w':/*!< Up key */
		case 's':/*!< Down key */
		default:
			// Unused
			break;
		}
		break;
	default:
		break;
	}
}
