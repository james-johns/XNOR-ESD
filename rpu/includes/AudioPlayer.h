/*!
 * @file AudioPlayer.h
 * @author James Johns
 */

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

/*!
 * @class AudioPlayer
 * @author James Johns
 * @brief Class for encapsulating audio playback.
 *
 * @details Pure Virtual interface for audio playback implementations
 */
class AudioPlayer {
public:
	AudioPlayer(const char *ipaddr);
	~AudioPlayer();

	virtual void pause() = 0;
	virtual void play() = 0;
	virtual bool isPlaying() = 0;
	virtual void rewind() = 0;
	virtual void fastForward() = 0;
	virtual void playpause() = 0; // trigger play when paused, pause when paying
	virtual bool listen() = 0; //Listens for incoming broadcast
	virtual void run() = 0;
	virtual void stop() = 0;

private:
};

#endif

