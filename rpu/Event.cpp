

#include <Event.h>

Event::Event(enum EventType_e nType, void *args)
{
	type = nType;
	arguments = args;
}

Event::~Event()
{

}
