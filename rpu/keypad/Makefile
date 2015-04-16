
testKeypad: testKeypad.cpp KeypadDevice.cpp ../includes/KeypadDevice.h
	g++ -I../includes -I/usr/include/libusb-1.0 -o testKeypad testKeypad.cpp KeypadDevice.cpp -lusb-1.0 -lpthread 

clean:
	rm testKeypad
