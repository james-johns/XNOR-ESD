


#all: testKeypad

#clean:
#	rm testKeypad
#
#testKeypad: testKeypad.o ../../keypad/KeypadDevice.o ../../includes/KeypadDevice.h
#	g++ -I../includes -I/usr/include/libusb-1.0 -o testKeypad testKeypad.cpp KeypadDevice.cpp -lusb-1.0 -lpthread 

#.cpp.o:
#	gcc -g -c -I../../includes/ -o $@ $<



obj-y:=../../keypad/KeypadDevice.o testKeypad.o

CROSS_COMPILE?=
DEBUG?=


CC:=$(CROSS_COMPILE)gcc
CXX:=$(CROSS_COMPILE)g++
LD:=$(CXX)
CFLAGS?=`pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
CXXFLAGS?=`pkg-config gstreamer-1.0 --cflags` `pkg-config libusb-1.0 --cflags` -I../../includes/ $(DEBUG)
LDFLAGS?=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lusb-1.0 -lpthread -lcurl

.PHONY: all clean testKeypad

all: testKeypad

clean:
	rm $(obj-y)
	rm testKeypad

testKeypad: $(obj-y)
	$(LD) -o $@ $(obj-y) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
