
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <queue>
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
	bool running = true;
	char *c;
	RPU *prog = (RPU *)arg;
	do {
		c = new char;
		scanf("%c", c);
		/*		switch (c) {
		case 'p':
			if (player->isPlaying())
				player->pause();
			else
				player->play();
			break;
		case 'r':
			player->rewind();
			break;
		default:
			break;
			}*/
		printf("Input: %c\n", *c);
		if (*c == 'q')
			running = false;
		prog->sendEvent(new Event(KEYPAD_INPUT, c));
	} while (running);
	delete c;

	prog->sendEvent(new Event(QUIT, NULL)); // send event to quit application

	return NULL;
}

int main(int argc, char **argv)
{
	bool running = true;
	/* Initialise required libraries */
	initGST(&argc, &argv);
	libusb_init(NULL);
	curl_global_init(CURL_GLOBAL_DEFAULT);

	/* Instantiate control objects */
	RPU *prog = new RPU(audioThreadEntry, ioThreadEntry);

	/* Enter state machine handling */
	Event *evt = NULL;
	do {
		if (evt != NULL) {
			delete evt;
			evt = NULL;
		}
		usleep(100);
		evt = prog->getEvent();
		if (evt != NULL) {
			// handle evt
			switch (evt->getType()) {
			case KEYPAD_INPUT:
				if (*(char *)evt->getArguments() == 'p')
					prog->getAudioPlayer()->play();
				break;
			case QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
	} while (running);

	/* shutdown procedure */
	delete prog;

	curl_global_cleanup();
	libusb_exit(NULL);
	gst_deinit();

	return 0;
}

