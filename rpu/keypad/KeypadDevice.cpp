

#include <KeypadDevice.h>
#include <stdio.h>
#include <unistd.h>

KeypadDevice::KeypadDevice()
{
	const int vendorId = 0x09ca;
	const int productId = 0x5544;
	
	libusb_device **deviceList;
	libusb_device *found = NULL;
	
	ssize_t count = libusb_get_device_list(NULL, &deviceList);
	ssize_t i = 0;
	int err = 0;
	
	struct libusb_device_descriptor desc;
	
	if (count < 0) {
		perror("No devices found");
		return;
	}
	
	for (i = 0; i < count; i++) {
		libusb_device *device = deviceList[i];
		libusb_get_device_descriptor(device, &desc);
		if(desc.idVendor == vendorId && desc.idProduct == productId) { //if this is the device we want...
			//printf("Found device!\n");
			found = device;
			break;
		}
		
	}
	
	if (found) {
		err = libusb_open(found, &handle);
		if (err) {
			handle = NULL;
			return;
		}
	}
	else {
		printf("No devices found\n");
		handle = NULL;
		return;
	}
	
	libusb_free_device_list(deviceList, 1);
	
	libusb_detach_kernel_driver(handle, 0);
	libusb_detach_kernel_driver(handle, 1);
	libusb_claim_interface(handle, 0);
	libusb_claim_interface(handle, 1);
}

KeypadDevice::~KeypadDevice()
{
	if (handle != NULL) {
		libusb_release_interface(handle, 0);
		libusb_release_interface(handle, 1);
		libusb_attach_kernel_driver(handle, 0);
		libusb_attach_kernel_driver(handle, 1);
		libusb_close(handle);
	}
}

void KeypadDevice::set7Seg(unsigned short value)
{
	sevenSegValue = value;
}

unsigned int KeypadDevice::getKeysPressed()
{
	return keysPressed;
}

int KeypadDevice::writeCommand(char * command, libusb_device_handle *handle)
{

}

int KeypadDevice::readPort(libusb_device_handle *handle)
{

}


void KeypadDevice::update()
{

}

