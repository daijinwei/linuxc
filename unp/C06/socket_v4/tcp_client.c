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
#include <math.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
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
	int nready;
	int maxfd;
	fd_set	read_set;
	char sendline[BUF_SIZE], recvline[BUF_SIZE];
	FD_ZERO(&read_set);

	for(; ;){
		FD_SET(fileno(fp), &read_set);	
		FD_SET(socketfd, &read_set);	
		maxfd = fileno(fp) > socketfd? fileno(fp) : socketfd;
		nready = select(maxfd + 1, &read_set, NULL, NULL, NULL);

		if(FD_ISSET(socketfd, &read_set)) {						// socket is readable
			if( -1 == read(socketfd, recvline, BUF_SIZE)) {
				return;	
			}
			fputs(recvline, stdout);
		}

		if(FD_ISSET(fileno(fp), &read_set)) {	// input is readable
			if(fgets(sendline, BUF_SIZE, fp) == NULL)
				return ;

			if ( -1 == write(socketfd, sendline, strlen(sendline))){
				handle_error("write the message to socket failed");
			}
		}
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
