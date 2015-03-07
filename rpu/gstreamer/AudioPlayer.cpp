
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

void AudioPlayer::run()
{
	gst_element_set_state(pipeline, GST_STATE_PLAYING);
	g_main_loop_run(loop);
}
