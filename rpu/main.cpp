
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <queue>
#include <sys/select.h>

#include <gst/gst.h>
#include <pthread.h>
#include <curl/curl.h>

#include <KeypadDevice.h>
#include <AudioPlayer.h>
#include <Event.h>
#include <RPU.h>

// initialise Gstreamer library
void initGST(int *argc, char ***argv)
{
	const gchar *nano_str;
	guint major, minor, micro, nano;

	gst_init(argc, argv);
	gst_version(&major, &minor, &micro, &nano);

	if (nano == 1)
		nano_str = "(CVS)";
	else if (nano == 2)
		nano_str = "(Prerelease)";
	else
		nano_str = "";

	printf ("This program is linked against GStreamer %d.%d.%d %s\n",
		major, minor, micro, nano_str);

}

// Thread for handling audio content
void *audioThreadEntry(void *arg)
{
	AudioPlayer *player = (AudioPlayer *)arg;
	player->run();
	std::cout << "Returning from audioThreadEntry" << std::endl;
	return NULL;
}

// Thread for handling IO
void *ioThreadEntry(void *arg)
{
	char *c;
	RPU *prog = (RPU *)arg;
	InputDevice *input = prog->getInputDevice();
	if (input->isConnected()) {
		do {
			for (int i = 0; i < 4; i++) {
				input->update();
				c = new char;
				*c = input->getKeyPressed();
				if (*c == '\n')
					delete c;
				else if (*c)
					prog->sendEvent(new Event(Event::KEYPAD_INPUT, c));
				else
					delete c;
			}
		} while (prog->isRunning());
	} else {
		fprintf(stderr, "No input device connected\n");
		prog->sendEvent(new Event(Event::QUIT, NULL)); // send event to quit application
	}

	return NULL;
}


/**
 * /fn main(int argc, char **argv)
 * /author James Johns
 *
 *
 */
int main(int argc, char **argv)
{
	/* Initialise required libraries */
	initGST(&argc, &argv);
	libusb_init(NULL);
	curl_global_init(CURL_GLOBAL_DEFAULT);

	/* Instantiate control objects */
	RPU *prog = new RPU(audioThreadEntry, ioThreadEntry);

	/* Enter state machine handling */
	do {
		prog->tick();
		usleep(100);
	} while (prog->isRunning());

	/* shutdown procedure */
	delete prog;

	curl_global_cleanup();
	libusb_exit(NULL);
	gst_deinit();

	return 0;
}

