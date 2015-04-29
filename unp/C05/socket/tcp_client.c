/*
 * =====================================================================================
 *
 *       Filename:  tcp_server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/29/2014 05:47:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50
#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)


typedef int SOCKETFD;

void str_cli(FILE *fp, SOCKETFD socketfd)
{
	char buf[BUF_SIZE];
	int n;
	char sendline[BUF_SIZE], recvline[BUF_SIZE];

	printf("~~~~~~* Please input the message *~~~~~~\n");
	while(fgets(sendline, BUF_SIZE, fp) != NULL) {
		n = write(socketfd, sendline, BUF_SIZE );	
		if (n < 0) {
			handle_error("write no  message");
		}

		if (0 == read(socketfd, recvline, BUF_SIZE)) {
			handle_error("read message failed");
		}

		fputs(recvline, stdout);
		printf("~~~~~~* Display the message *~~~~~~\n");
	}
}

int main(int argc, char *argv[])
{
	if (3 != argc) {
		handle_error("Usage: tcp_client <IPaddress> <port>");
	}

	int	sockfd;
	int server_port = atoi(argv[2]);	
	socklen_t	clientlen;
	struct sockaddr_in 	client_addr, server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		handle_error("create socket failed\n");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);

	inet_pton(AF_INET, argv[1] ,&server_addr.sin_addr);
	
	if(-1 == connect(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr))){
		handle_error("connect socket failed\n");
	}

	str_cli(stdin, sockfd);
	exit(0);
}
