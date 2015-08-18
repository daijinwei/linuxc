#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLEN 1024

int main(int argc, char* argv[])
{
	int ret;
	int sockfd, n;
	char recvline[MAXLEN];
	struct sockaddr_in6 server_addr;

	if (2 != argc){
		printf("Usage: ./day_time_tcp_cli <IPaddress>\n");
		exit(EXIT_FAILURE);
	}

	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0){
		printf("sock failed\n");
		exit(EXIT_FAILURE);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_port = htons(13);		// Day time server

	if((inet_pton(AF_INET6, argv[1], &server_addr.sin6_addr) <= 0)) {// inet_pton, support for ipv4 and ipv6
		printf("inet_pton failed\n");	
		exit(EXIT_FAILURE);
	}

	if ((ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0){
		printf("connect to server failed\n");
		exit(EXIT_FAILURE);
	}	

	while( (n = read(sockfd, recvline, MAXLEN)) > 0){
		recvline[n] = '\0';
		if(fputs(recvline, stdout) == EOF){
			printf("connect to server failed\n");
			exit(EXIT_FAILURE);
		}
	}
	

	if(n < 0){
		exit(EXIT_FAILURE);
	}

	return 0;
}
