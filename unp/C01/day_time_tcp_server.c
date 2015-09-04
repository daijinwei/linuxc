#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "log.h"

#define MAX_LEN 1024
#define BACK_LOG 1024

int main(int argc, char* argv[])
{
	int ret;
	int sockfd, connect_fd;
        char buffer[MAX_LEN];
        const char *message = NULL;
	struct sockaddr_in server_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
                LOG(ERROR, "create socket failed\n");
		exit(EXIT_FAILURE);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(13);		// Day time server, port: 0-1024,Permission should be root

	if ( -1 == (ret = bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)))){
                message = strerror(errno);
                LOG(ERROR, "Bind the sockaddr to socket failed, %s\n", message);
		exit(EXIT_FAILURE);
	}	

        if (-1 == (ret = listen(sockfd, BACK_LOG))){
                LOG(ERROR, "Seting listening socket failed\n");
		exit(EXIT_FAILURE);
        }

        for ( ; ; ){
                if( -1 == (connect_fd = accept(sockfd, (struct sockaddr*) NULL,NULL))){
                        message = strerror(errno);
                        LOG(ERROR, "Seting listening socket failed, %s\n", message);
                        exit(EXIT_FAILURE);
                }

                time_t ticks = time(NULL);
                snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
                if ((ret = write(connect_fd, buffer, strlen(buffer))) < 0){
                        LOG(ERROR, "Seting listening socket failed, %s\n", message);
                }
                close(connect_fd);
        }
        close(sockfd);
	return 0;
}
