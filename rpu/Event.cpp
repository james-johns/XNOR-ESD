/*!
 * @file Event.cpp
 * @author James Johns
 */

#include <Event.h>

/*! Event::Event(enum EventType_e nType, void *args)
 * @author James Johns
 * @brief Event constructor
 *
 * @param[in] nType Type of event for new Event.
 * @param[in] args Arguments for new Event.
 */
Event::Event(enum EventType_e nType, void *args)
{
	type = nType;
	arguments = args;
}

/*! Event::~Event()
 * @author James Johns
 * @brief Event destructor
 */
Event::~Event()
{

}
