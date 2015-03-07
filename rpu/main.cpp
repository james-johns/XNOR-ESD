
#include <stdio.h>
#include <iostream>
#include <gst/gst.h>
#include <pthread.h>

#include <KeypadDevice.h>
#include <AudioPlayer.h>

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

void *audioThreadEntry(void *arg)
{
	AudioPlayer *player = (AudioPlayer *)arg;
	player->run();
	std::cout << "Returning from audioThreadEntry" << std::endl;
	return NULL;
}

void *ioThreadEntry(void *arg)
{
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t audioThread, ioThread;

	/* Initialise required libraries */
	initGST(&argc, &argv);
	libusb_init(NULL);

	/* Instantiate control objects */
	KeypadDevice *keypad = new KeypadDevice();	
	AudioPlayer *player = new AudioPlayer();

	/* Create threads */
	if (pthread_create(&audioThread, NULL, audioThreadEntry, player) != 0) {
		perror("Could not create audio thread");
	}

	/* Enter state machine handling */
	char c;
	do {
		scanf("%c", &c);
		switch (c) {
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
		}
	} while (c != 'q');

	/* shutdown procedure */
	player->stop();
	pthread_join(audioThread, NULL);
	delete player;
	delete keypad;

	return 0;
}

