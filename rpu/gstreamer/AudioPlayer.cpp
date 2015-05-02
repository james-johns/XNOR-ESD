/*!
 * @file AudioPlayer.cpp
 * @author James Johns
 */
#include <iostream>

#include <AudioPlayer.h>
#include <gst/gst.h>

/*! AudioPlayer::AudioPlayer(const char *ipaddr)
 * @author James Johns
 * @brief AudioPlayer constructor
 *
 * @param[in] ipaddr IP Address to connect to when receiving audio
 *
 * @details Creates and initialises a Gstreamer pipeline to stream audio over TCP port 3000,
 * decode, convert and playback the audio stream via an alsa device.
 */
AudioPlayer::AudioPlayer(const char *ipaddr)
{
	std::string pipelineString = "tcpserversrc host=";
	pipelineString += (ipaddr != NULL) ? ipaddr : "127.0.0.1";
	pipelineString += " port=3000 ! decodebin ! audioconvert ! alsasink";
	pipeline = gst_parse_launch(pipelineString.c_str(), NULL);
	gst_element_set_state(pipeline, GST_STATE_PAUSED);

	loop = g_main_loop_new(NULL, FALSE);
}

/*! AudioPlayer::AudioPlayer(const char *ipaddr)
 * @author James Johns
 * @brief AudioPlayer destructor
 *
 * @details Kills the Gstreamer pipeline during deletion of the AudioPlayer object
 */
AudioPlayer::~AudioPlayer()
{
	stop(); /*!< Stop playing audio before unreferencing pipeline */
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
}

/*! AudioPlayer::run()
 * @author James Johns
 * @brief Run the Gstreamer pipeline
 *
 * @details Begin running the gstreamer main loop for this player.
 * Blocks until the main loop quits.
 */
void AudioPlayer::run()
{
	g_main_loop_run(loop);
}

/*! AudioPlayer::stop()
 * @author James Johns
 * @brief Stop the Gstreamer pipeline
 *
 * @details Stop the audio player from running.
 * Any calls to AudioPlayer::run() will return.
 */
void AudioPlayer::stop()
{
	g_main_loop_quit(loop);
}

/*! AudioPlayer::pause()
 * @author James Johns
 * @brief Pause the Gstreamer pipeline
 *
 * @details Set the audio pipeline to paused
 */
void AudioPlayer::pause()
{
	gst_element_set_state(pipeline, GST_STATE_PAUSED);
}

/*! AudioPlayer::play()
 * @author James Johns
 * @brief Play the Gstreamer pipeline
 *
 * @details Set the audio pipeline to play
 */
void AudioPlayer::play()
{
	gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

/*! AudioPlayer::playpause()
 * @author James Johns
 * @brief Toggle the Gstreamer pipeline between play and pause state
 *
 */
void AudioPlayer::playpause()
{
	if (isPlaying())
		pause();
	else
		play();
}

/*! AudioPlayer::isPlaying()
 * @author James Johns
 * @brief Find if the Gstreamer pipeline is playing
 * @returns True if pipeline is playing, else false.
 */
bool AudioPlayer::isPlaying()
{
	GstState state;
	gst_element_get_state(pipeline, &state, NULL, 0);
	return (state == GST_STATE_PLAYING);
}

/*! AudioPlayer::rewind()
 * @author James Johns
 * @brief Rewind the Gstreamer pipeline
 *
 * @details rewind the current playing stream by 5 seconds, or to the beginning of the stream; 
 * whichever is closer to the current position
 */
void AudioPlayer::rewind()
{
	gint64 nano;
	gst_element_query_position(pipeline, GST_FORMAT_TIME, &nano);
	if (nano < (5 * GST_SECOND))
		nano = 5 * GST_SECOND;
	gst_element_seek_simple(pipeline, GST_FORMAT_TIME, 
				GstSeekFlags(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT), 
				nano - (5 * GST_SECOND));
}
