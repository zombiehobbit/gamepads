#include "tcp_client.h"
//#define DEBUG

int connect_client(const char *address,unsigned int port)
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; /* connector's address information */

	//const char *adr = "127.0.0.1"; // constant char for address
	const char *adr = address; // this is some kind of odd, but quck, fix.

	//if (he=gethostbyname(address) == NULL)
	if((he = gethostbyname(adr)) == NULL)
	{
		printf("%s\n","getting host name failed");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("%s\n","what in the name of @#$#$# failed to assign fd for socket");
		return -1;
	}

	their_addr.sin_family = AF_INET; // byte for the for host
	their_addr.sin_port = htons(port); // switching over to network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr); 
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	// connect the socket
	if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr)) == -1)
	{
		printf("%s\n","could not connect to the client...");
		return -1;
	}


	return sockfd;
}

int send_string(int sockfd,char *msg)
{
	int sent_bytes,bytes_to_send;
	bytes_to_send = strlen(msg);
	while(bytes_to_send > 0)
	{
		sent_bytes = send(sockfd,msg,bytes_to_send,0);
		if(sent_bytes == -1)
		{
			return 0;
		}

		bytes_to_send -= sent_bytes;
		msg += sent_bytes;
	}
	return 1;
}

int parse_command(const char *device,const char *command,char *buffer)
{
	//json_object data;
}

int send_gamepad_data(int sockfd,int mainjoystick_x,int mainjoystick_y,int main_button)
{
	// Convert all those stuff for a mashine
	char joystickx[16];
	char joysticky[16];
	bool mbutton;
	
	sprintf(joystickx,"%d",mainjoystick_x);
	sprintf(joysticky,"%d",mainjoystick_y);

	

	#ifdef DEBUG
	printf("joystick x: %s\n",joystickx);
	printf("joystick y: %s\n",joysticky);
	
	// NOTE: 1 line rule used here.
	printf("mbutton: ");
	if(mbutton == true)
		printf("%s\n","true");
	else
		printf("%s\n","false");

	#endif

	return -1; // stub
}

// int connect(car_server *server, char *address,unsigned short port)
// {
// 	server-> he = gethostbyname(address);
// 	server-> sock_fd =  socket(AF_INET, SOCK_STREAM);
//
// 	if(server->he == -1) // host lookup failed
// 		return -1;
//
// 	if(server->sock_fd == -1) // failed to connect socket
// 		return -1;
//
// 	their_addr.sin_family = AF_INE
// 	their_addr.sin_port = htons(PORT);
// 	their_addr.sin_addr = *((struct in_addr *)server->he->h_addr);
//
//
// 	return 0; // stub
// }
