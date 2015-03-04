
#include <stdio.h>
#include <unistd.h>

//Bare-bones implementation of James' RPU FSD

#define SERVER_WORKING 0

void flush()
{
    int ch;
    while ((ch=getchar()) != EOF && ch != '\n');
}

int login()
{
    char input;

    printf("Login prompt. Enter your login details (c for login, other for failure).\n");

    //Get login number
    flush();
    input = getchar();

    if(input == 'c') {   //If login is valid:
        printf("Login success\n");
        return 0; //Return success
    }
    else { //If login is invalid
        printf("Login failure. Waiting five seconds.\n");
        sleep(5);
        return 1; //Return failure
    }


}

int audioPlayback()
{
    printf("Audio playback\n\n");

    if(SERVER_WORKING) {
        printf("Playback success\n");
    }
    else {
        printf("Playback failure\n Waiting 5 seconds\n");
        sleep(5);
    }
}

int playbackControl()
{
    printf("Playback control!\n\n");
}

int language()
{
    printf("Language options\nEnglish, German.\n\n");
}

int knowledge()
{
    printf("Knowledge options\nBeginner, intermediate, advanced.\n(I know these aren't the actual levels\n\n");
}

int menu()
{
    char input;
    int loggedIn = 1;

    while(loggedIn) {

        printf("This is the menu.\n l to select language.\n k to select knowledge level\n o to log out\n a for audio playback\n p for playback control\n");

        flush();
        input = getchar();

        switch(input) {

            case 'p':
                playbackControl();
                break;
            case 'a':
                audioPlayback();
                break;
            case 'l':
                language();
                break;
            case 'k':
                knowledge();
                break;
            case 'o':
                printf("Logging out\n\n");
                loggedIn = 0;
                break;
            default:
                printf("Invalid\n");
                break;
        }
    }
}

int main()
{
    int result;

    while(1) {

        //Login prompt
        do {
            printf("Please log in\n");
        } while(login()); //Loop until successful login

        //Display menu
        menu();

        printf("Done\n");
    }

    //Get login info

    //If login fail

    return 0;
}
