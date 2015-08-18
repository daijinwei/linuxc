#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

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

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(13);		// Day time server


	if ((ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0){
		printf("bind the socket failed\n");
		exit(EXIT_FAILURE);
	}	

        if (-1 == (ret = listen(listen_fd, BACK_LOG))){
		printf("listen the socket failed\n");
		exit(EXIT_FAILURE);
        }

        for ( ; ; ){
                if((connect_fd = accept(listen_fd, (struct sockaddr*) NULL,NULL))){
                        printf("connect to server failed\n");
                        exit(EXIT_FAILURE);
                }
                time_t ticks = time(NULL);
                snprintf(buffer, sizeof(buffer),"%.24s\r\n", ctime(&ticks));
                if ((ret = write(connect_fd, buffer, strlen(buffer))) < 0){
                        printf("write message to connect_fd failed\n"); 
                }
                close(connect_fd);
        }
	return 0;
}
