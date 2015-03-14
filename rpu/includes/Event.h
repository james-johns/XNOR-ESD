

#ifndef _EVENT_H_
#define _EVENT_H_

enum EventType_e {
	KEYPAD_INPUT, MULTICAST_REQUEST, QUIT
};

class Event {
public:
	Event(enum EventType_e type, void *args);
	~Event();

	enum EventType_e getType() { return type; }
	void *getArguments() { return arguments; }
private:
	enum EventType_e type;
	void *arguments;
};



#endif
