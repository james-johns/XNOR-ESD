/*!
 * @file Event.h
 * @author James Johns
 */
#ifndef _EVENT_H_
#define _EVENT_H_

/*!
 * @class Event
 * @author James Johns
 * @brief Event object for storing event states
 */
class Event {
public:

        /*!
	 * @enum EventType_e
	 */
	enum EventType_e {
		KEYPAD_INPUT,  /*!< Input event is an input event. Argument will be the input character. */
		MULTICAST_REQUEST,  /*!< Multicast stream is requesting to start. */
		QUIT /*!< Device is requesting to quit. */
	};


	Event(enum EventType_e type, void *args);
	~Event();

	/*! Event::getType()
	 * @brief Get event type.
	 * @returns EventType_e of this event.
	 */
	enum EventType_e getType() { return type; }

	/*! Event::getType()
	 * @brief Get event arguments.
	 * @returns Arguments for this event. Type is generic, and should be cast depending on the event type.
	 */
	void *getArguments() { return arguments; }
private:
	enum EventType_e type; /*!< Event type */
	void *arguments; /*!< Event argument */
};



#endif
