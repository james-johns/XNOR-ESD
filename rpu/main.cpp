
#include <stdio.h>
#include <gst/gst.h>
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

int main(int argc, char **argv)
{
	initGST(&argc, &argv);
	libusb_init(NULL);
	KeypadDevice *keypad = new KeypadDevice();
	
	AudioPlayer *player = new AudioPlayer();
	player->run();


	return 0;
}

