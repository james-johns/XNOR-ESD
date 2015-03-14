
#include <iostream>

#include <AudioPlayer.h>
#include <gst/gst.h>

AudioPlayer::AudioPlayer()
{
	pipeline = gst_parse_launch("tcpserversrc host=127.0.0.1 port=3000 ! decodebin ! audioconvert ! alsasink", NULL);
	gst_element_set_state(pipeline, GST_STATE_PAUSED);

	loop = g_main_loop_new(NULL, FALSE);
}

AudioPlayer::~AudioPlayer()
{
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
}

// Begin running the gstreamer main loop for this player.
// Blocks until the main loop quits.
void AudioPlayer::run()
{
	std::cout << "Running AudioPlayer" << std::endl;
	g_main_loop_run(loop);
}

// Stop the audio player from running.
// Any calls to AudioPlayer::run() will return.
void AudioPlayer::stop()
{
	g_main_loop_quit(loop);
}

// Pause the audio pipeline
void AudioPlayer::pause()
{
	gst_element_set_state(pipeline, GST_STATE_PAUSED);
}

// Play the audio pipeline
void AudioPlayer::play()
{
	gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

bool AudioPlayer::isPlaying()
{
	GstState state;
	gst_element_get_state(pipeline, &state, NULL, 0);
	return (state == GST_STATE_PLAYING);
}

// rewind the current playing stream by 5 seconds, or to the beginning of the stream; 
// whichever is closer to the current position
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
