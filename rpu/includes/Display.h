

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Display{
public:
	Display();
	~Display();

	void setPlaybackString(const char *str) { playbackString = str; playbackDirty = true; }
	void setMenuString(const char *str) { menuString = str; menuDirty = true; }
	void setTrackInfoString(const char *str) { trackInfoString = str; trackInfoDirty = true; }
	void displayError(const char *str) { errorString = str; }

	virtual void refresh() = 0; /*!< Use to update display device */
protected:
	const char *playbackString;
	const char *menuString;
	const char *trackInfoString;
	const char *errorString;
	bool playbackDirty, menuDirty, trackInfoDirty;
};

#endif

