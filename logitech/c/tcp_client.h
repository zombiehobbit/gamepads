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
#define MAXDATASIZE 100 /* max number of bytes we can get at once */

int connect_client(const char *address,unsigned int port);
int send_string(int sockfd,char *msg);
int send_gamepad_data(int sockfd,int mainjoystick_x,int mainjoystick_y,int main_button); // send data from the gamepad to a tcp client

#endif
