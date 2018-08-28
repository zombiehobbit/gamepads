/** Filename: main.c
 *
 *  Description:
 *
 *      Open connection to gamepad on path /dev/input/jso
 *      Read and print gamepad events and values
 *
 *     ctrl + c  terminates program
 *
 */


#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//#include <curses.h>
#include <termios.h> // included for doing the non blocking keyboard stuff 
#include "gamepad.h"
#include "tcp_client.h"
#include "nonblockingInput.h"
// do some dumb typing stuff
#define KEYBOARD 0
#define GAMEPAD 1

volatile bool keepRunning = true;

// signal interrupt handler
void intHandler(){
    keepRunning = false;
}


int main()
{
	char inputDevice = GAMEPAD;
	struct termios term_settings; // keyboard only settings.  Only unly used when we're running in keyboard mode 
	
    int sockfd=-1; // socket to the client
    sockfd = connect_client("127.0.0.1",9999); // open a tcp connection to the robot car, or some other server 

	if(sockfd == -1)
	{
		printf("%s\n","could not connect to server... \n press enter to continue. \n I'm sorry. :( I'm doing my");
		getc(stdin);
	}

    const char defaultPath[64] = "/dev/input/js0";

    gamepad gpad;
    ssize_t bytesRead;
    int incompleteReadCount = 0;

    initGamepadStruct(&gpad);

    // set up signal interrupt for ctrl+c
    struct sigaction act;
    act.sa_handler = intHandler;        // assign signal interrupt handler function
    sigaction(SIGINT, &act, NULL);      // ctrl+c generates SIGINT

    if (sigfillset(&act.sa_mask) < 0){
        puts("sigfillset failed");
        return 1;
    }

    act.sa_flags=0;
    if (sigaction(SIGINT,&act,0) < 0){ // Setup signal
        puts("sigaction failed");
        return 1;
    }


    // open connection to gamepad
    if(connectGamepad(defaultPath, &gpad)){
        fprintf(stderr, "gamepad initialized\n");
		printDeviceInfo(&gpad);
    }else{
        fprintf(stderr, "program termination, gamepad initialize failed\n");
        destructGamepad(&gpad);
		// failed to open gamepad, now using keyboard
		printf("%s\n","gamepad could not be opened, now using keyboard interface");
		inputDevice = KEYBOARD;
    }

    //printDeviceInfo(&gpad);

	// if inputDevice is a keyboard, then configure for non blocking IO
	// I know that this could be done in the preceding if statement, but I think this is more readable 

	if(inputDevice == KEYBOARD)
	{
		SetKeyboardNonBlock(&term_settings);
	}


    while(keepRunning)
    {
        /* read(int fd, void *buf, size_t count)
            read attempts to read up to count bytes from the
            file descriptor fd and store the bytes in buf

            not an error if less bytes are read

            returns -1 for error
        */

		if(inputDevice == GAMEPAD)
		{
        	bytesRead = read (gpad.fd, &gpad.event, sizeof(struct js_event));

        	// bytesRead may not equal the number of bytes requested
        	if(bytesRead == sizeof(struct js_event)){
            	//printEventInfo(&gpad);
            	//send_string(sockfd,"joystick stuff happend");
				//int jspos = getMainJoystick(&gpad); // NOTE: Function deleted 
        	}
        	else if(bytesRead == -1){
            	fprintf(stderr, "error reading gamepad, %s\n", strerror(errno));
            	keepRunning = false;
        	}
        	else{
         	   fprintf(stderr, "warning, read %ld bytes, requested %ld\n", bytesRead, sizeof(struct js_event));
            	++incompleteReadCount;
            	if(incompleteReadCount >= 4){
                	keepRunning = false;
            	}
        	}
		}
		else if(inputDevice == KEYBOARD)
		{
			// do non blocking keyboard input stuff here...
			char key = 0;
			key = getchar();
			
			if(key == 'w')
			{
				printf("%s\n","up");
			}
			if(key == 's')
			{
				printf("%s\n","down");
			}
			if(key == 'a')
			{
				printf("%s\n","left");
			}			
			if(key == 'd')
			{
				printf("%s\n","right");
			}

			// test for a quit condition
			if(key == 'q')
			{
				printf("%s\n","quit button pressed, good bye!");
				keepRunning = false;
			}


	// this is the old way of doing this.  We're using a spiffy new way.  See the non bloc
/*
			//char keyin = getchar();king input header file 
			char keyin = getch();
			switch(keyin)
			{
				case 'w':
					printf("%s\n","UP");
					break;
				case 's':
					printf("%s\n","DOWN");
			}
*/
			
		}
    } // end while

    // disconnect from the host
    if(sockfd > -1)
    {
      printf("%s\n","closing socket");
      send_string(sockfd,"halt");
      close(sockfd);
    }
	else
	{
		printf("%s\n","if nothing worked, than was was b/c gamepad was never connected to the socket");
	}

	if(inputDevice == GAMEPAD)
	{
    	printf("%s\n","disconnecting game pad");
    	destructGamepad(&gpad);
	}
	else if(inputDevice == KEYBOARD) // if we're in keyboard mode then reset back to normal 
	{
		printf("%s\n","resetting terminal back into normal mode...");
		RestoreKeyboardBlocking(&term_settings);
	}

    return 0;
}
