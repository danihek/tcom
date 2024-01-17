#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[])
{
	// check if provided arguments
	if (argv[1]==0)
	{
	   printf("Usage: tcom [command]");
		exit(1);
	}

	// set all required variables to create connection
	int
	port = 6969;
	int
	bufferSize = 1024;
	int // create socket with UDP comunication
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	char
	buffer[bufferSize];
	char
	*ip = "0.0.0.0";

	struct
	sockaddr_in addr;

	socklen_t
	addr_size;
	
	// print error when cant create socket
	if (sockfd == -1)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}

	// set address family
	addr.sin_family = AF_INET;
 	// set port to operate with
	addr.sin_port = htons(port);
	// convert char*ip and put it in addr.sin_addr
	if (inet_pton(AF_INET, ip, &addr.sin_addr)<=0)
	{
		perror("inet_pton() error");
		exit(EXIT_FAILURE);
	}
	// store size of server address as variable
	addr_size = sizeof(addr);
	
	// copy 'command' from argv to buffer
	strcpy(buffer,argv[1]);

	// send command to execute on server
	sendto(sockfd,buffer,bufferSize,0,(struct sockaddr*)&addr,addr_size);
		
	// fill buffer with zeros
	bzero(buffer, bufferSize);

	return 0;
}
