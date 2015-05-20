/*!
 * @file RPU.h
 * @author James Johns
 * @brief Controller class for RPU system
 *
 * Central control class for RPU.
 */


#ifndef _RPU_H_
#define _RPU_H_

#include <pthread.h>
#include <queue>

#include <Event.h>
#include <InputDevice.h>
#include <AudioPlayer.h>
#include <Display.h>
#include <Menu.hpp>
#include <CDDWebApi.h>

/*!
 * @class RPU
 * @author James Johns
 * @brief Main controller class for RPU system
 *
 */
class RPU {
public:
	RPU(void *(*audioThreadEntry)(void *), void *(*ioThreadEntry)(void *));
	~RPU();
	
	void tick(); // handle events and manage other objects

	void sendEvent(Event *evt);
	Event *getEvent();


        /*! RPU::getInputDevice
	 * @author James Johns
	 * @brief Return current input device.
	 *
	 * @return Current input device.
	 */
	InputDevice *getInputDevice() { return input; }
	Display *getDisplay() { return display; }

        /*! RPU::isRunning()
	 * @author James Johns
	 * @brief RPU running state
	 *
	 * @return TRUE if RPU is running, FALSE if shutting down or should shutdown.
	 */
	bool isRunning() { return running; }

	static std::vector<char *> *getIPAddress();

private:
        /*!
	 * @enum RPUState_e
	 *
	 * @brief Enumerator for maintaining RPU state
	 */
	enum RPUState_e {
		LOGIN_PROMPT, /*!< RPU requires PIN to unlock and use */
		DISPLAY_MENU, /*!< Display global menu */
		SELECT_LANGUAGE, /*!< Display menu to select language */
		SELECT_KNOWLEDGE, /*!< Display menu to select Knowledge */
		REQUEST_STREAM /*!< Request an audio stream from CDD */
	};

	bool running; /*!< True when RPU is running. False when exiting/should exit. */
	enum RPUState_e state; /*!< Holds RPU state to determine action on next tick. */
	std::queue<Event *> *eventQueue; /*!< Event Queue for events sent to RPU. */
	InputDevice *input; /*!< Input device object. Must not be NULL */
	Display *display; /*!< Display device object. Must not be NULL */
	AudioPlayer *player; /*!< Audio player object. NULL if no audio currently playing. */
	pthread_t audioThread, /*!< pthread handle the Audio thread */
		  ioThread; /*!< pthread handles for IO thread */
	Menu *mainMenu;
	std::string numberInput;
	CDDWebApi *cddapi;

	void loginPrompt(Event *evt);
	void displayMenu(Event *evt);
	void selectLanguage(Event *evt);
	void selectKnowledge(Event *evt);
	void requestStream(Event *evt);
};

#endif
