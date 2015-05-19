

obj-y:=main.o Event.o RPU.o keypad/KeypadDevice.o audioplayer/GSTAudioPlayer.o audioplayer/AudioPlayer.o cddapi/CDDWebApi.o keypad/KeyboardDevice.o display/LCDDisplay.o display/Display.o display/NCursesDisplay.o Menu.o audioplayer/VLCAudioPlayer.o

CROSS_COMPILE?=
DEBUG?=-g


CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?=`pkg-config libusb-1.0 --cflags` $(DEBUG)
CXXFLAGS?=`pkg-config gstreamer-1.0 --cflags` `pkg-config libusb-1.0 --cflags` `pkg-config ncurses --cflags` -I./includes $(DEBUG)
LDFLAGS?=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lusb-1.0 -lpthread -lcurl -lncurses -lvlc

.PHONY: all clean rpuclient

all: rpuclient

clean:
	rm $(obj-y)
	rm rpuclient

rpuclient: $(obj-y)
	$(LD) -o $@ $(obj-y) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
