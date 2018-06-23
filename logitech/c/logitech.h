
/** Filename: logitech.h
 * 
 *  Decription: 
 * 
 * 
 *  References:
 *  https://www.kernel.org/doc/Documentation/input/joystick-api.txt
 *  https://github.com/torvalds/linux/blob/master/include/uapi/linux/joystick.h 
 */


#ifndef LOGITECH_H_INCLUDED
#define LOGITECH_H_INCLUDED


#include <stdbool.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <unistd.h>



/*
    Left joystick:

    Direction of Movement      Event Type    Event number        Range of values

    Forward                         Axis            1               0 to -32767
    Backward                        Axis            1               0 to  32767
    Left                            Axis            0               0 to -32767
    Right                           Axis            0               0 to  32767

    Right joystick:

    Left                            Axis            2               0 to -32767
    Right                           Axis            2               0 to  32767
    Forward                         Axis            3               0 to -32767
    Backward                        Axis            3               0 to  32767

    Forward facing buttons:

    5 Upper Left                    Button          4               1 when pressed, 0 not pressed
    7 Lower Left                    Button          6               1 when pressed, 0 not pressed
    6 Upper Right                   Button          5               1 when pressed, 0 not pressed
    8 Lower Right                   Button          7               1 when pressed, 0 not pressed

    Numbered Buttons:
    1                               Button          0               1 when pressed, 0 not pressed
    2                               Button          1               1 when pressed, 0 not pressed
    3                               Button          2               1 when pressed, 0 not pressed
    4                               Button          3               1 when pressed, 0 not pressed
    9                               Button          8               1 when pressed, 0 not pressed
    9                               Button          9               1 when pressed, 0 not pressed

    Top Thumb Controller
    Forward                         Axis            5               -32767 when pressed, 0 not pressed
    Backward                        Axis            5                32767 when pressed, 0 not pressed
    Left                            Axis            4               -32767 when pressed, 0 not pressed
    Right                           Axis            4                32767 when pressed, 0 not pressed

    Return to center, value = 0

*/


#define JOY_AXIS_MAX 32767

// The linux driver found in linux/joystick.h reports events in the form
/*typedef struct
{
  uint32_t time;        // event timestamp in milliseconds
  int16_t value;
  uint8_t type;         // event type
  uint8_t number;       // axis button number
} js_event;
*/


typedef struct gamepad_t{
    char *devicePath;                   // path name
    char *deviceName;                   
    int  fd;                            // file descriptor
    int  numButtons;                    // number of buttons
    int  numAxes;                       // number of axes
    struct js_event  event;
} gamepad;



// Function prototype declaration
void initGamepadStruct(gamepad *gpad);
bool connectGamepad(const char *defaultPath, gamepad *gpad);


void destructGamepad(gamepad *gpad);

void printDeviceInfo(const gamepad *gpad);
void printEventInfo(const gamepad *gpad);


#endif // LOGITECHJOYSTICK_H_INCLUDED