
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <KeyboardDevice.h>
#include <Event.h>

KeyboardDevice::KeyboardDevice()
{

}

KeyboardDevice::~KeyboardDevice()
{

}

void KeyboardDevice::update()
{
	fd_set fds;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(fileno(stdin), &fds);
	char c;
	if (select(1, &fds, NULL, NULL, &tv) > 0) {
		scanf("%c", &c);
		
		if (c != '\n') {
			lastKeyPressed = c;
		}
	}
}

char KeyboardDevice::getKeyPressed()
{
	char temp = lastKeyPressed;
	lastKeyPressed = 0;
	return temp;
}

