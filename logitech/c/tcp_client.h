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

	typedef struct 
	{
		int sock_fd;
		struct hostent *he;
        	struct sockaddr_in their_addr;
	}car_server;

	int connect(car_server*,char*,unsigned short);
	int destory(car_server*);
	int send_gamepad(const gamepad *);
	

#endif
