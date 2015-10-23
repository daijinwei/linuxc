#ifndef _CONNECTTIMEOUT_H
#define _CONNECTTIMEOUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
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


#define handle_msg(msg)	\
	do{ 					\
		printf(msg); 		\
	}while(0)

typedef int SOCKETFD;

void str_cli(FILE *fp, SOCKETFD socketfd);

int connect_timeo(int sockfd, const struct sockaddr *addr, socklen_t len, int timeout);

#endif //:_CONNECTTIMEOUT_H
