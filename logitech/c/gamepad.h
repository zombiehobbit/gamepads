#ifndef GAMEPAD_H
#define GAMEPAD_H
#include <stdbool.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <unistd.h>

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
int getMainJoystick(const gamepad *gpad);

#endif // LOGITECHJOYSTICK_H_INCLUDED


