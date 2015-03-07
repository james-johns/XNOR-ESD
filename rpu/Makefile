

obj-y:=main.o keypad/KeypadDevice.o gstreamer/AudioPlayer.o

CROSS_COMPILE?=
GST_LIBRARY_PATH?=

CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?= `pkg-config libusb-1.0 --cflags`
CXXFLAGS?=`pkg-config gstreamer-1.0 --cflags` `pkg-config libusb-1.0 --cflags` -I./includes
LDFLAGS?=$(GST_LIBRARY_PATH) -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lusb-1.0 -lpthread

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