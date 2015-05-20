/*!
 * @file GSTAudioPlayer.h
 * @author Rob Shepherd
 */

#ifndef _VLCAUDIO_PLAYER_H_
#define _VLCAUDIO_PLAYER_H_

#include <AudioPlayer.h>
#include <vlc/vlc.h>

/*!
 * @class VLCAudioPlayer
 * @author Rob Shepherd
 * @brief Class for encapsulating VLC audio playback.
 *
 * @details Uses VLC to playback audio from a remote streaming source
 */
class VLCAudioPlayer : public AudioPlayer {
public:
	VLCAudioPlayer(const char *ipaddr);
	~VLCAudioPlayer();

	void pause();
	void play();
	bool isPlaying();
	void rewind();
	void playpause(); // trigger play when paused, pause when paying

	bool listen(); //Listens for incoming broadcast

	void run();
	void stop();

private:
	libvlc_instance_t *vlc;
	libvlc_media_player_t *vlc_str;
	libvlc_media_player_t *vlc_bc;
	libvlc_media_t *vlc_m;

	unsigned int counter; //Used for timing in listen()

	std::string url;
};

#endif

