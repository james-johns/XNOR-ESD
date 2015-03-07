

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include <gst/gst.h>

class AudioPlayer {
public:
	AudioPlayer();
	~AudioPlayer();

	void pause();
	void play();

	void run();
	void stop();

private:
	GstElement *pipeline;
	GMainLoop *loop;
};

#endif

