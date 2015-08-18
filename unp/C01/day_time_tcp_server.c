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
	int listen_fd, connected_fd;
	char recvline[MAXLEN];
	struct sockaddr_in server_addr;

	if ((listen_d = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("sock failed\n");
		exit(EXIT_FAILURE);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
    server_addr.sin_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(13);		// Day time server


	if ((ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0){
		printf("connect to server failed\n");
		exit(EXIT_FAILURE);
	}	

    if (-1 == (ret = listen(listen_fd, BACK_LOG))){
		printf("listen the socket failed\n");
		exit(EXIT_FAILURE);
    }

    for ( ; ;  ) {
        if(connected_fd = accept(listen_fd, NULL, NULL))  {
		    printf("caccept failed\n");
		    exit(EXIT_FAILURE);
        }  
    }
	return 0;
}
