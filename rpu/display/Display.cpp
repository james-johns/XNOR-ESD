
#include <iostream>

#include <Display.h>

Display::Display()
{
	setMenuString(NULL);
	setTrackInfoString(NULL);
	setPlaybackString(NULL);
	displayError(NULL);
}

Display::~Display()
{

}

