

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Display{
public:
	Display();
	~Display();

	void setPlaybackString(char *str) { playbackString = str; playbackDirty = true; }
	void setMenuString(char *str) { menuString = str; menuDirty = true; }
	void setTrackInfoString(char *str) { trackInfoString = str; trackInfoDirty = true; }

	virtual void refresh() = 0; /*!< Use to update display device */
protected:
	char *playbackString;
	char *menuString;
	char *trackInfoString;
	bool playbackDirty, menuDirty, trackInfoDirty;
};

#endif

