

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include <gst/gst.h>

class AudioPlayer {
public:
	AudioPlayer(const char *ipaddr);
	~AudioPlayer();

	void pause();
	void play();
	bool isPlaying();
	void rewind();
	void playpause(); // trigger play when paused, pause when paying


	void run();
	void stop();

private:
	GstElement *pipeline;
	GMainLoop *loop;
};

#endif

