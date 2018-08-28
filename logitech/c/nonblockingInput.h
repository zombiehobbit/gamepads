#ifndef NONBLOCK
#define NONBLOCK
#include <termios.h>
#include <stdlib.h>
void RestoreKeyboardBlocking(struct termios *initial_settings);
void SetKeyboardNonBlock(struct termios *initial_settings);

#endif
