
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libusb.h"

#define INTERFACE 0
#define DEBUG 0

//0 = no messages
//1 = errors on stderr
//2 = errors and warnings on stderr
//3 = messages on stdout, errors and warnings on stderr
#define DEBUG_LEVEL 3

//Returns number of devices
int numberOfDevices()
{
    libusb_device **list; //Array of detected devices

    int ret;

    int num =  libusb_get_device_list(NULL, &list);

    if(num > 0) {
        ret = num;
    }
    else {
        perror("libusb_get_device_list");
        ret = 0;
    }

    libusb_free_device_list(list, 1);

    return ret;
}

int getDesc(libusb_device * device, struct libusb_device_descriptor * desc)
{
    int result = libusb_get_device_descriptor(device, desc);

    if (result < 0) {
        return 0;
    }

    /*printf("%04x:%04x (bus %d, device %d)\n",
    desc->idVendor, desc->idProduct,
    libusb_get_bus_number(device), libusb_get_device_address(device));
    */
    return 1;
}

//Using code from libusb 1.0 documentation (device handling and enumeration)
libusb_device_handle * getHandle()
{
    const int vendorId = 0x09ca;
    const int productId = 0x5544;

    libusb_device_handle *handle;

    libusb_device **deviceList;
    libusb_device *found = NULL;

    ssize_t count = libusb_get_device_list(NULL, &deviceList);
    ssize_t i = 0;
    int err = 0;

    struct libusb_device_descriptor desc;

    if (count < 0) {
        error();
    }

    for (i = 0; i < count; i++) {
        libusb_device *device = deviceList[i];
        getDesc(device, &desc);
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
        }
    }
    else {
        printf("No devices found\n");
        handle = NULL;
    }

    libusb_free_device_list(deviceList, 1);

    libusb_detach_kernel_driver(handle, 0);
    libusb_detach_kernel_driver(handle, 1);
    libusb_claim_interface(handle, 0);
    libusb_claim_interface(handle, 1);
    return handle;
}


//Send the specified command to the PIO
//Returns 1 on error
int writeCommand(char * command, libusb_device_handle *handle)
{
    int result;
    int length;

    const int max = 8;

    unsigned char data[max];
    unsigned char rx[max];

    int i = 0;

    if(strlen(command) > max) {
        fprintf(stderr, "Command too long\n");
        return 1;
    }

    //Convert command string into char array for transfer
    while(i < strlen(command) && i < max) {
        data[i] = command[i];
        if(DEBUG) {
            printf("%c", data[i]);
        }
        i++;
    }

    if(DEBUG) {
        printf("\n");
    }

    result = libusb_bulk_transfer(handle, 1, data, i, &length, 0);

    if(result != 0 || length != i) {
        printf("Problem!\n");
        error();
        return 1;
    }

    result = libusb_bulk_transfer(handle, 0x82, rx, max, &length, 0);
    //Need to check result

    if(DEBUG || data[5] == '?') {
        printf("\t");
        for(i = 0; i < length; i++) {
            printf("%c", rx[i]);
        }
        printf("\n", i);
    }

    return 0;
}

int readPort(libusb_device_handle *handle)
{
    int result;
    int length;
    char data[10];

    result = libusb_bulk_transfer(handle, 0x82, data, 10, &length, 0);

    int i = 0;
    for(i = 0; i < length; i++) {
        printf("%c", data[i]);
    }

    printf("\n");
}

//Return 7seg data byte for numbers 0-9
void numToSeg(int num, char chars[2])
{
    char lookup[10][2] = {"3F", "06", "5B", "4F", "66", "6D", "7D", "07", "7F", "6F"};

    chars[0] = lookup[num][0];
    chars[1] = lookup[num][1];
}

void testDevice(libusb_device_handle *handle)
{
    //Pn selects port number, followed by 8 bits of data
    //Pn followed by a ? reads data from the port
    //Dn is used to set port direction. 00 for output, FF for input

    int i = 0;
    int j = 0;
    int result;

    //Init commands (empty command used as terminator)
    //Set up output ports
    char *commands[10] = {"@00D000\r", "@00D1FF\r", "@00D200\r", ""};

    char test[10] = {'@','0','0','P','2','0','0','\r','\0'};
    char select[10] = {'@', '0', '0', 'P', '0', '0', '0', '\r', '\0'};
    char readIn[10] = {'@', '0', '0', 'P', '1', '?', '\r', '\0'};

    int len;

    const int rate = 60; //Number of updates per second
    int delay = 1000000/(rate*4); //usleep delay to use

    result = libusb_reset_device(handle);
    if (result < 0) {
        fprintf(stderr, "Unable to reset device\n");
        return;
    }

    sleep(1);

    //Send init commands
    for(i = 0; i < 10; i++) {
        if(commands[i] != "") {
            if(DEBUG) {
                printf("C%d:\t", i);
            }

            len = strlen(commands[i]);
            result = writeCommand(commands[i], handle);
            if(result > 0) {
                printf("Problem!\n");
                return;
            }

        }
        else {
            break;
        }
    }

    char numData[2];


    for(i = 0; i < 4; i++) {

        writeCommand(test, handle);

        select[6] = '0' + (1 << i);
        writeCommand(select, handle);

        for(j = 0; j < 10; j++) {
            numToSeg(j, numData);
            test[5] = numData[0];
            test[6] = numData[1];
            writeCommand(test, handle);
            usleep(50000);
            writeCommand(readIn, handle);
        }
    }

    //Clear 7 segs
    test[5] = '0';
    test[6] = '0';
    writeCommand(test, handle);
}

int main()
{
    int ret = libusb_init(NULL);
    libusb_device_handle *handle;

    if (ret > 0) {
        perror("libusb_init");
        return ret;
    }

    libusb_set_debug(NULL, DEBUG_LEVEL);

    printf("There are %d devices\n", numberOfDevices());

    handle = getHandle();

    if(handle == NULL) {
        fprintf(stderr, "Failed to get USB device handle; stopping.\n");
        return 1;
    }

    testDevice(handle);

    //Cleanup
    libusb_release_interface(handle, 0);
    libusb_release_interface(handle, 1);
    libusb_attach_kernel_driver(handle, 0);
    libusb_attach_kernel_driver(handle, 1);
    libusb_close(handle);
    libusb_exit(NULL);

    return 0;
}
