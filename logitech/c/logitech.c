/** Filename: logitech.h
 * 
 *  Decription: Defines functions
 * 
 *      to connect to a logitech gamepad
 *      read and display the gamepad values
 * 
 * 
 *  References:
 *  https://www.kernel.org/doc/Documentation/input/joystick-api.txt
 *  https://github.com/torvalds/linux/blob/master/include/uapi/linux/joystick.h 
 */


#include "logitech.h"

#include <fcntl.h>
#include <errno.h>
#include <string.h>                     // strcpy, strlen
#include <stdio.h>                      // fprintf
#include <stdlib.h>                     // malloc
#include <sys/ioctl.h>




void initGamepadStruct(gamepad *gpad)
{
    gpad->devicePath = NULL;
    gpad->deviceName = NULL;
    gpad->numButtons = 0;
    gpad->numAxes = 0;
    gpad->event.type = 0;
    gpad->event.time = 0;
    gpad->event.value = 0;
    gpad->event.number = 0;
}



bool connectGamepad(const char *defaultPath, gamepad *gpad)
{
    // opening in a blocking mode
    gpad->fd = open(defaultPath,O_RDONLY);

	if (gpad->fd == -1)
	{
		fprintf(stderr, "error: %s, %d, unable to open device path: %s\n", __FUNCTION__, __LINE__, defaultPath);
		return false;
	}
	else
	{
		fprintf(stderr, "success: %s, opened device path: %s, file descriptor: %d\n", __FUNCTION__, defaultPath, gpad->fd);

		/*  After the open it will issue a series of synthetic events
        *   (JS_EVENT_INIT) that you can read to check the initial state of the
        *   joystick.
        */

        char buttons;
        char axes;
        char name[128];

        /*  The joystick driver defines the following ioctl(2) operations. */

                                            /* function			3rd arg  */
		//  #define JSIOCGAXES	            /* get number of axes		char	 */
		//  #define JSIOCGBUTTONS	        /* get number of buttons	char	 */
		//  #define JSIOCGVERSION	        /* get driver version		int	 */
		//  #define JSIOCGNAME(len)         /* get identifier string	char	 */
		//  #define JSIOCSCORR	            /* set correction values	&js_corr */
		//  #define JSIOCGCORR	            /* get correction values	&js_corr */


        // get number of buttons
        if(ioctl (gpad->fd, JSIOCGBUTTONS, &buttons) == 0){
             gpad->numButtons = buttons;
        }
        else{
            fprintf(stderr, "error: %s, line: %d, %s\n", __FUNCTION__, __LINE__, strerror(errno));
            return false;
        }
       

        // get number of axes
        if(ioctl (gpad->fd, JSIOCGAXES, &axes) == 0){
             gpad->numAxes = axes;
        }
        else{
            fprintf(stderr, "error: %s, line: %d, %s\n", __FUNCTION__, __LINE__, strerror(errno));
            return false;
        }

        // get device name
        if (ioctl(gpad->fd, JSIOCGNAME (sizeof(name)), name) == 0){
             gpad->deviceName = (char*)malloc(sizeof(strlen(name)+1*sizeof(char)));
            strcpy(gpad->deviceName, name);
        }
        else
        {
            fprintf(stderr, "warning: %s, setting device name as unknown, %s\n", __FUNCTION__, strerror(errno));
            gpad->deviceName = (char*)malloc(sizeof("unknown"));
            strcpy(gpad->deviceName, "unknown");
        }
	}
	return true;

}


void destructGamepad(gamepad *gpad){

    // free dynamically allocated memory
    if(gpad->devicePath != NULL){
        free(gpad->devicePath);
        gpad->devicePath = NULL;
    }

    if(gpad->deviceName != NULL){
        free(gpad->deviceName);
        gpad->deviceName = NULL;
    }

    if(gpad->fd){
         close(gpad->fd);
    }
}


void printDeviceInfo(const gamepad *gpad)
{
    fprintf(stderr, "Device name: %s\n", gpad->deviceName);
    fprintf(stderr, "Number of buttons = %d\n", gpad->numButtons);
    fprintf(stderr, "Number of axes =    %d\n", gpad->numAxes);
}


void printEventInfo(const gamepad *gpad)
{
    /* The possible values of ``type'' are

		#define JS_EVENT_BUTTON         0x01     button pressed/released
		#define JS_EVENT_AXIS           0x02     joystick moved
		#define JS_EVENT_INIT           0x80     initial state of device
    */

    switch (gpad->event.type)
    {
        case JS_EVENT_BUTTON:
            printf("Button pressed, event.number = %d, event.value = %d\n", gpad->event.number, gpad->event.value);
        break;

        case JS_EVENT_AXIS:
            printf("Axis, joystick moved, event.number = %d, event.value = %d\n", gpad->event.number, gpad->event.value);
        break;
        case JS_EVENT_BUTTON | JS_EVENT_INIT:
            printf("JS_EVENT_BUTTON | JS_EVENT_INIT\n");
        break;
        case JS_EVENT_AXIS | JS_EVENT_INIT:
            printf("JS_EVENT_AXIS | JS_EVENT_INIT\n");
        break;
        default:
            printf("Unknown joystick event\n");
    }
}

