#ifndef TCP_CL
#define TCP_CL
#define PORT 9999
#define BUFFOUT 80
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/joystick.h>
#include "gamepad.h"

int connect(unsigned char *address,unsigned int port);
int sendString(int sockfd,char *msg);

#endif
