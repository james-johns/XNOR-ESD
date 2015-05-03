

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Display{
public:
	Display();
	~Display();

	void setPlaybackString(const char *str);
	void setMenuString(const char *str);
	void setTrackInfoString(const char *str);
	void displayError(const char *str);

	virtual void refresh() = 0; /*!< Use to update display device */
protected:
	const char *playbackString;
	const char *menuString;
	const char *trackInfoString;
	const char *errorString;
	bool playbackDirty, menuDirty, trackInfoDirty, errorDirty;
};

#endif

