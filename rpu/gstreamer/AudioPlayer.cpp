
#include <iostream>

#include <AudioPlayer.h>
#include <gst/gst.h>

AudioPlayer::AudioPlayer()
{
	pipeline = gst_parse_launch("audiotestsrc ! decodebin ! alsasink", NULL);
	gst_element_set_state(pipeline, GST_STATE_PAUSED);

	loop = g_main_loop_new(NULL, FALSE);
}

AudioPlayer::~AudioPlayer()
{
	
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
