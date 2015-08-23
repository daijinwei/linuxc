#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024
#define BACK_LOG 1024

int main(int argc, char* argv[])
{
	int ret;
	int listen_fd, connect_fd;
        char buffer[MAX_LEN];
	struct sockaddr_in server_addr;

	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("sock failed\n");
		exit(EXIT_FAILURE);
	}

        printf("sockfd: %d\n", listen_fd);
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(13);		// Day time server

	if ( -1 == (ret = bind(listen_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)))){
                perror("bind failed\n");
		printf("bind the socket failed\n");
		exit(EXIT_FAILURE);
	}	

        if (-1 == (ret = listen(listen_fd, BACK_LOG))){
		printf("listen the socket failed\n");
		exit(EXIT_FAILURE);
        }

        for ( ; ; ){
                if( -1 == (connect_fd = accept(listen_fd, (struct sockaddr*) NULL,NULL))){
                        perror("accept to server failed\n");
                        exit(EXIT_FAILURE);
                }

                time_t ticks = time(NULL);
                snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
                if ((ret = write(connect_fd, buffer, strlen(buffer))) < 0){
                        printf("write message to connect_fd failed\n"); 
                }
                close(connect_fd);
        }
	return 0;
}
