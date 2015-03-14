
#include <iostream>

#include <KeypadDevice.h>
#include <pthread.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

//#define _THREADED_

#ifdef _THREADED_

void *updateThreadFunc(void *arg)
{
    KeypadDevice *keypad = (KeypadDevice *) arg;

    while(1) {
        keypad->update();
    }
}

#endif

int main(int argc, char **argv)
{
    pthread_t updateThread;

    libusb_init(NULL);

    std::cout << "Starting keypad" << std::endl;
    KeypadDevice *keypad = new KeypadDevice();
    keypad->set7Seg(""); //Clears display


    #ifdef _THREADED_
    std::cout << "Creating thread" << std::endl;
    if (pthread_create(&updateThread, NULL, updateThreadFunc, keypad) != 0) {
        perror("Could not create thread");
        return 1;
    }
    #endif

    char key;
    std::string data;
    int input;

    while(1) {
        #ifndef _THREADED_
        keypad->update(); //Refresh 7 seg and scan keypad
        #endif

        key = keypad->getKeyPressed();

        if(key) {
            if(key == 'F') {  //Enter key: confirm and display input number
                input = atoi(data.c_str());
                std::cout << "Entered " << input << std::endl;
                data = "";
            }
            else if(key == 'E') { //Cancel key: remove last number
                if(data.length() > 0) {
                    data.erase(data.length()-1, 1);
                }
            }
            else if(key && data.length() != 4) {   //Accept another number if there is space
                if(key >= '0' && key <= '9') {     //Append key character to data string and display it
                    data += key;
                }
            }

            keypad->set7Seg(data);
        }
        #ifdef _THREADED_
        usleep(100000); //Arbitrary delay
        #endif
    }

    return 0;
}
