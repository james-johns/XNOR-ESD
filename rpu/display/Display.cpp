
#include <iostream>
#include <cstring>

#include <stdlib.h>
#include <pthread.h>

#include <Display.h>

Display::Display()
{
	menuString = NULL; menuDirty = true; pthread_mutex_init(&menuMutex, NULL);
	trackInfoString = NULL; trackInfoDirty = true; pthread_mutex_init(&trackInfoMutex, NULL);
	playbackString = NULL; playbackDirty = true; pthread_mutex_init(&playbackMutex, NULL);
	errorString = NULL; errorDirty = true; pthread_mutex_init(&errorMutex, NULL);
}

Display::~Display()
{
	pthread_mutex_lock(&playbackMutex);
	pthread_mutex_lock(&menuMutex);
	pthread_mutex_lock(&trackInfoMutex);
	pthread_mutex_lock(&errorMutex);
	if (playbackString != NULL) delete playbackString;
	if (menuString != NULL) delete menuString;
	if (trackInfoString != NULL) delete trackInfoString;
	if (errorString != NULL) delete errorString;
	pthread_mutex_destroy(&playbackMutex);
	pthread_mutex_destroy(&menuMutex);
	pthread_mutex_destroy(&trackInfoMutex);
	pthread_mutex_destroy(&errorMutex);
}

void Display::setPlaybackString(const char *str)
{
	char *tmp = NULL;
	if (str != NULL) {
		tmp = new char[strlen(str)+1];
		strncpy(tmp, str, strlen(str)+1);
	}
	pthread_mutex_lock(&playbackMutex);
	if (playbackString != NULL) {
		delete playbackString;
	}
	playbackString = tmp;
	playbackDirty = true;
	pthread_mutex_unlock(&playbackMutex);
}

char *Display::getPlaybackString(char **buffer)
{
	if (buffer == NULL)
		return NULL;

	pthread_mutex_lock(&playbackMutex);
	if (playbackString == NULL) {
		*buffer = NULL;
	} else {
		int strLength = strlen(playbackString) + 1; // strlen does not include null terminator
		*buffer = (char *) malloc(sizeof(char) * strLength);
		strncpy(*buffer, playbackString, strLength); // will copy all, including null terminator
	}
	pthread_mutex_unlock(&playbackMutex);
	return *buffer;
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

char *Display::getMenuString(char **buffer)
{
	if (buffer == NULL)
		return NULL;

	pthread_mutex_lock(&menuMutex);
	if (menuString == NULL) {
		*buffer = NULL;
	} else {
		int strLength = strlen(menuString) + 1; // strlen does not include null terminator
		*buffer = (char *) malloc(sizeof(char) * strLength);
		strncpy(*buffer, menuString, strLength); // will copy all, including null terminator
	}
	pthread_mutex_unlock(&menuMutex);
	return *buffer;
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

char *Display::getTrackInfoString(char **buffer)
{
	if (buffer == NULL)
		return NULL;

	pthread_mutex_lock(&trackInfoMutex);
	if (trackInfoString == NULL) {
		*buffer = NULL;
	} else {
		int strLength = strlen(trackInfoString) + 1; // strlen does not include null terminator
		*buffer = (char *) malloc(sizeof(char) * strLength);
		strncpy(*buffer, trackInfoString, strLength); // will copy all, including null terminator
	}
	pthread_mutex_unlock(&trackInfoMutex);
	return *buffer;
}

void Display::setErrorString(const char *str)
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

char *Display::getErrorString(char **buffer)
{
	if (buffer == NULL)
		return NULL;

	pthread_mutex_lock(&errorMutex);
	if (errorString == NULL) {
		*buffer = NULL;
	} else {
		int strLength = strlen(errorString) + 1; // strlen does not include null terminator
		*buffer = (char *) malloc(sizeof(char) * strLength);
		strncpy(*buffer, errorString, strLength); // will copy all, including null terminator
	}
	pthread_mutex_unlock(&errorMutex);
	return *buffer;
}

