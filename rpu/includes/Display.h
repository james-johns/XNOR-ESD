

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <pthread.h>

class Display{
public:
	Display();
	~Display();

	void setPlaybackString(const char *str);
	char *getPlaybackString(char **buffer);
	bool playbackIsDirty() { return playbackDirty; }
	void setPlaybackDirty(bool dirty) { playbackDirty = dirty; }

	void setMenuString(const char *str);
	char *getMenuString(char **buffer);
	bool menuIsDirty() { return menuDirty; }
	void setMenuDirty(bool dirty) { menuDirty = dirty; }

	void setTrackInfoString(const char *str);
	char *getTrackInfoString(char **buffer);
	bool trackInfoIsDirty() { return trackInfoDirty; }
	void setTrackInfoDirty(bool dirty) { trackInfoDirty = dirty; }

	void setErrorString(const char *str);
	char *getErrorString(char **buffer);
	bool errorIsDirty() { return errorDirty; }
	void setErrorDirty(bool dirty) { errorDirty = dirty; }

	virtual void refresh() = 0; /*!< Use to update display device */
private:
	const char *playbackString; pthread_mutex_t playbackMutex;
	const char *menuString; pthread_mutex_t menuMutex;
	const char *trackInfoString; pthread_mutex_t trackInfoMutex;
	const char *errorString; pthread_mutex_t errorMutex;
	bool playbackDirty, menuDirty, trackInfoDirty, errorDirty;
};

#endif

