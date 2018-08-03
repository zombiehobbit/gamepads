#include "tcp_client.h"

int connect(car_server *server, char *address,unsigned short port)
{
	server-> he = gethostbyname(address);
	server-> sock_fd =  socket(AF_INET, SOCK_STREAM);
	
	if(server->he == -1) // host lookup failed
		return -1;

	if(server->sock_fd == -1) // failed to connect socket
		return -1;
		
	their_addr.sin_family = AF_INE
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *)server->he->h_addr);
	

	return 0; // stub
}
