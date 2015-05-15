


obj-y:=../../cddapi/CDDWebApi.o testCDDApi.o

CROSS_COMPILE?=
DEBUG?=


CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?=`pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
CXXFLAGS?=`pkg-config gstreamer-1.0 --cflags` `pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
LDFLAGS?=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lusb-1.0 -lpthread -lcurl

.PHONY: all clean testkeypad

all: testCDDApi

clean:
	rm $(obj-y)
	rm testCDDApi

testCDDApi: $(obj-y)
	$(LD) -o $@ $(obj-y) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
