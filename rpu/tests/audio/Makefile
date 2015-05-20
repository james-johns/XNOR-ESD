

obj-y:=../../audioplayer/AudioPlayer.o ../../audioplayer/VLCAudioPlayer.o main.o

CROSS_COMPILE?=
DEBUG?=


CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?=`pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
CXXFLAGS?=`pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
LDFLAGS?=-lusb-1.0 -lpthread -lcurl -lvlc

.PHONY: all clean main

all: main

clean:
	rm $(obj-y)
	rm main

main: $(obj-y)
	$(LD) -o $@ $(obj-y) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
