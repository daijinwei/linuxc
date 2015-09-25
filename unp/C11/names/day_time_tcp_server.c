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
#include "tcp_listen.h"
#include "log.h"

#define MAX_LEN 1024
#define BACK_LOG 1024

int main(int argc, char* argv[])
{
	int ret;
	int sockfd, connect_fd;
    char buffer[MAX_LEN];
    const char *message = NULL;
	struct sockaddr_in server_addr, client_addr;

    sockfd = tcp_listen(NULL, argv[1], NULL);
    if (0 > sockfd) {
        LOG(ERROR, "Seting listening socket failed\n");
    }

    for ( ; ; ){
        socklen_t len = sizeof(struct sockaddr);
        if( -1 == (connect_fd = accept(sockfd, (struct sockaddr*) &client_addr, &len))){
            message = strerror(errno);
            LOG(ERROR, "Connect  failed, %s\n", message);
            exit(EXIT_FAILURE);
        }
        printf("connection from %s: port %d\n", inet_ntop(AF_INET, &client_addr, buffer, sizeof(buffer)), ntohs(client_addr.sin_port));

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
