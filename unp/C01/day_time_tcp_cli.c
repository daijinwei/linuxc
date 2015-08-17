#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLEN 1024

int main(int argc, char* argv[])
{
	int sockfd, n;
	char recvline[MAXLEN];
	struct sockaddr_in server_addr;

	if (2 != argc){
		printf("Usage: ./day_time_tcp_cli <IPaddress>\n");
		exit(EXIT_FAILURE);
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("sock failed\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
