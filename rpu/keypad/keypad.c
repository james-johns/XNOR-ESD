
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

        libusb_detach_kernel_driver(handle, 0);
        libusb_detach_kernel_driver(handle, 1);
        libusb_claim_interface(handle, 0);
        libusb_claim_interface(handle, 1);
    }
    else {
        printf("No devices found\n");
        handle = NULL;
    }

    libusb_free_device_list(deviceList, 1);

    return handle;
}


//Send the specified command to the PIO
//Returns 1 on error
int writeCommand(char * command, char * buffer, libusb_device_handle *handle)
{
    int result;
    int length;

    const int max = 8;

    unsigned char data[max];

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

    if(buffer != NULL) { //If an input buffer was provided...
        result = libusb_bulk_transfer(handle, 0x82, buffer, 8, &length, 0);
        //Need to check result

        if(DEBUG) {// || data[5] == '?') { //Print result if it was a read operation
            printf("\t");
            for(i = 0; i < length; i++) {
                printf("%c", buffer[i]);
            }
            printf("\n", i);
        }
    }

    return 0;
}

//Return 7seg data byte for numbers 0-9
//Need to extend to hex chars and .
void digitToSeg(unsigned int num, char chars[2])
{
    char lookup[10][2] = {"3F", "06", "5B", "4F", "66", "6D", "7D", "07", "7F", "6F"};

    chars[0] = lookup[num][0];
    chars[1] = lookup[num][1];
}

void charToSeg(char input, char output[2])
{
    char lookup[17][2] = {"3F","06","5B","4F","66","6D","7D","07","7F","6F","77","7C","39","5E","79","71","80"};

    if(input == '.') {
        input = 16; //'.' is the final entry in the array
    }
    else if(input >= '0' && input <= '9') {
        input -= '0'; //Get offset from 0 character
    }
    else if(input >= 'A' && input <= 'F') {
        input -= 'A'; //Get offset from A character (numbers and letters are not contiguous)
        input += 10; //Continue lookup after 9
    }
    else{
        output[0] = '0';
        output[1] = '0';
        return;
    }

    output[0] = lookup[input][0];
    output[1] = lookup[input][1];
}

//Needs support for hex chars and .
void numToSeg(char data[4][2], unsigned int number)
{
    unsigned int temp;
    int subtract;

    int i, j, k;

    //Mask number to get individual digits
    //for(i = 3; i >= 0; i--) {  //For each 7 seg...
    for(i = 0; i < 4; i++) {  //For each 7 seg...
        k = 1;
        for(j = 3-i; j != 0 ; j--) { //Get the base value of its digit (1, 10, 100, 1000)
            k *= 10;
        }

        temp = number / k;
        number -= temp * k;

        digitToSeg(temp, data[i]); //Convert number to hex chars for 7 seg
    }
}

void displayNumber(int number, libusb_device_handle *handle)
{
    char output[4][2];
    char commandRead[10] = {'@','0','0','P','1','?','\r','\0'};
    char commandWrite[10] = {'@','0','0','P','2','0','0','\r','\0'};
    char commandSelect[10] = {'@','0','0','P','0','0','0','\r','\0'};

    const char lookup [4][4] = {{'1','4','7','A'}, {'2','5','8','0'}, {'3', '6', '9', 'B'}, {'F', 'E', 'D', 'C'}};

    unsigned char input[8];
    char pressedChar;
    char pressedColumn; //Column of pressed button (i)

    unsigned int i, j;
    unsigned int digit;

    char data[2] = {'0','0'};

    //numToSeg(output, 1234); //Populate output with hex chars to send to 7 seg

    while(1) {
        for(i = 0; i < 4; i++) { //For each 7 seg...

            //Select appropriate 7 seg
            commandSelect[6] = '0' + (1 << i);
            writeCommand(commandSelect, input, handle);

            //Write number to display
            commandWrite[5] = data[0]; //Get hex chars from array
            commandWrite[6] = data[1];
            writeCommand(commandWrite, input, handle);
            usleep(5000); //Need to calculate delay from desired refresh rate

            //Clear 7 seg before selecting the next one (makes for a cleaner display)
            commandWrite[5] = '0';
            commandWrite[6] = '0';
            writeCommand(commandWrite, input, handle);

            //Read from keypad
            writeCommand(commandRead, input, handle);
            digit = (input[4] - '0'); //Get row of pressed button (1,2,4,8)

            if(digit > 0 && !pressedChar) { //Check for button press, unless there is one currently pressed
                digit /= 2; //Convert 1,2,4,8 to 0,1,2,3 for lookup table
                if(digit == 4) {
                    digit--;
                }
                pressedChar = lookup[i][digit];
                charToSeg(pressedChar, data); //Set write data to be the pressed char
                //printf("%c\n", pressedChar); //Get value of pressed button
                pressedColumn = i;
            }
            else if(pressedChar){
                if(digit == 0 & i == pressedColumn){
                    pressedChar = 0;
                    data[0] = '0';
                    data[1] = '0';
                }
            }
        }
    }
}

void resetDevice(libusb_device_handle *handle)
{
    char *commands[10] = {"@00D000\r", "@00D1FF\r", "@00D200\r", ""};

    int i, len, result;

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
            result = writeCommand(commands[i], NULL, handle);
            if(result > 0) {
                printf("Problem!\n");
                return;
            }

        }
        else {
            break;
        }
    }
}

void testDevice(libusb_device_handle *handle)
{
    //Pn selects port number, followed by 8 bits of data
    //Pn followed by a ? reads data from the port
    //Dn is used to set port direction. 00 for output, FF for input


    resetDevice(handle);


    displayNumber(1248, handle);


    //Create thread which rotates through select pins, writing data buffer to 7 seg and reading keypad into read buffer
    //Current thread handles top level functionality
}

libusb_device_handle *openKeypadDevice()
{
    int ret = libusb_init(NULL);

    if (ret > 0) {
        perror("libusb_init");
        return NULL;
    }

    libusb_device_handle *handle;

    libusb_set_debug(NULL, DEBUG_LEVEL);

    printf("There are %d devices\n", numberOfDevices());

    handle = getHandle();

    if(handle == NULL) {
        fprintf(stderr, "Failed to get USB device handle; stopping.\n");
        return NULL;
    }
    return handle;
}

void closeKeypadDevice(libusb_device_handle *handle)
{
//    testDevice(handle);

    //Cleanup
    libusb_release_interface(handle, 0);
    libusb_release_interface(handle, 1);
    libusb_attach_kernel_driver(handle, 0);
    libusb_attach_kernel_driver(handle, 1);
    libusb_close(handle);
    libusb_exit(NULL);

}
