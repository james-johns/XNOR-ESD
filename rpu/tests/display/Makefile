


obj-y:=../../display/LCDDisplay.o ../../display/Display.o testDisplay.o

CROSS_COMPILE?=
DEBUG?=


CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?=`pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
CXXFLAGS?=`pkg-config gstreamer-1.0 --cflags` `pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
LDFLAGS?=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lusb-1.0 -lpthread -lcurl

.PHONY: all clean testKeypad

all: testDisplay

clean:
	rm $(obj-y)
	rm testDisplay

testDisplay: $(obj-y)
	$(LD) -o $@ $(obj-y) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
