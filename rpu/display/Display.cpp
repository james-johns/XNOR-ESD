
#include <iostream>
#include <cstring>

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
	if (playbackString != NULL) delete playbackString;
	if (menuString != NULL) delete menuString;
	if (trackInfoString != NULL) delete trackInfoString;
	if (errorString != NULL) delete errorString;
}

void Display::setPlaybackString(const char *str)
{
	char *tmp = NULL;
	if (playbackString != NULL) {
		delete playbackString;
	}
	if (str != NULL) {
		tmp = new char[strlen(str)+1];
		strncpy(tmp, str, strlen(str)+1);
	}
	playbackString = tmp;
	playbackDirty = true;
}

void Display::setMenuString(const char *str)
{
	char *tmp = NULL;
	if (menuString != NULL) {
		delete menuString;
	}
	if (str != NULL) {
		tmp = new char[strlen(str)+1];
		strncpy(tmp, str, strlen(str)+1);
	}
	menuString = tmp;
	menuDirty = true;
}

void Display::setTrackInfoString(const char *str)
{
	char *tmp = NULL;
	if (trackInfoString != NULL) {
		delete trackInfoString;
	}
	if (str != NULL) {
		tmp = new char[strlen(str)+1];
		strncpy(tmp, str, strlen(str)+1);
	}
	trackInfoString = tmp;
	trackInfoDirty = true;
}

void Display::displayError(const char *str)
{
	char *tmp = NULL;
	if (errorString != NULL) {
		delete errorString;
	}
	if (str != NULL) {
		tmp = new char[strlen(str)+1];
		strncpy(tmp, str, strlen(str)+1);
	}
	errorString = tmp;
	errorDirty = true; 
}
