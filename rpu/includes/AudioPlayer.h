/*!
 * @file AudioPlayer.h
 * @author James Johns
 */

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include <gst/gst.h>

/*!
 * @class AudioPlayer
 * @author James Johns
 * @brief Class for encapsulating audio playback.
 *
 * @details Uses libGstreamer to playback audio from a remote streaming source
 */
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
	GstElement *pipeline; /*!< Gstreamer pipeline used for audio streaming */
	GMainLoop *loop; /*!< Gstreamer thread handle for pipelin execution */
};

#endif

