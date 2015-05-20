/*!
 * @file GSTAudioPlayer.h
 * @author James Johns
 */

#ifndef _GSTAUDIO_PLAYER_H_
#define _GSTAUDIO_PLAYER_H_

#include <gst/gst.h>

#include <AudioPlayer.h>

/*!
 * @class GSTAudioPlayer
 * @author James Johns
 * @brief Class for encapsulating LibGstreamer audio playback.
 *
 * @details Uses libGstreamer to playback audio from a remote streaming source
 */
class GSTAudioPlayer : public AudioPlayer {
public:
	GSTAudioPlayer(const char *ipaddr);
	~GSTAudioPlayer();

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

