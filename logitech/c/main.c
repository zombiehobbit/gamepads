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
#include "logitech.h"

volatile bool keepRunning = true;

// signal interrupt handler
void intHandler(){
    keepRunning = false;
}


int main()
{
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
    if(connectGamepad(defaultPath, &gpad))
        fprintf(stderr, "gamepad initialized\n");
    else{
        fprintf(stderr, "program termination, gamepad initialize failed\n");
        destructGamepad(&gpad);
    }
        
    printDeviceInfo(&gpad);


    while(keepRunning)
    {
        /* read(int fd, void *buf, size_t count)
            read attempts to read up to count bytes from the 
            file descriptor fd and store the bytes in buf

            not an error if less bytes are read

            returns -1 for error 
        */
        bytesRead = read (gpad.fd, &gpad.event, sizeof(struct js_event));

        // bytesRead may not equal the number of bytes requested
        if(bytesRead == sizeof(struct js_event)){
            printEventInfo(&gpad);
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
    } // end while

    
    destructGamepad(&gpad);
    return 0;
}