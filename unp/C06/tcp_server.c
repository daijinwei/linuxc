#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50

#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)

int main()
{
	int	maxfd, maxi, i, listen_fd, connect_fd, sockfd, n, len;
    int nready, client[FD_SETSIZE];
    char buf[BUF_SIZE];
	struct sockaddr_in 	client_addr, server_addr;
    fd_set rset;
	socklen_t	clientlen;
	int port = 8080;	

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listen_fd) {
		handle_error("create socket failed\n");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	if(-1 == bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
		handle_error("bind socket failed\n");
	}

	if (-1 == listen(listen_fd, LISTEN_BACKLOG)){
		handle_error("listen socket failed\n");
	}

    maxi = -1;
    maxfd = listen_fd;
    // Init client[]
    for (i = 0; i < FD_SETSIZE; ++i) {
        client[i] = -1;
    }

    FD_ZERO(&rset);
    FD_SET(listen_fd, &rset);
	for (; ;) {
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (-1 == nready) {
            printf("select error"); 
        }

        if (FD_ISSET(listen_fd, &rset)) {
		    clientlen = sizeof(client_addr);
		    if ((connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &clientlen)) < 0){
                if (errno == EINTR) {
                    continue; 
                }

            }
            for (i = 0; i < FD_SETSIZE; i++){
                if (client[i] < 0){
                    client[i] = connect_fd;
                    break;
                }
            }

            if (i > FD_SETSIZE){
		        handle_error("too many connect\n");
            }
            FD_SET(connect_fd, &rset);

            // max i
            if(i > maxi){
                maxi = i; 
            }

            if(--nready < 0){   // No more readable description
                continue; 
            }
        }

        for (i = 0; i <= maxi; ++i){
            sockfd = client[i]; 
            if (sockfd < 0){
                continue; 
            }

            if (FD_SET(sockfd, &rset)) {
                n = read(sockfd, buf, BUF_SIZE);
                if (-1 == n) {
		            handle_error("read the message failed\n");
                    continue;
                }else if(0 == n){
                    FD_CLR(sockfd, &rset); 
                    client[i] = -1;
                    close(sockfd);
                }else{
                    len = write(sockfd, buf, n); 
                    if (-1 == len){
		                handle_error("write the message failed\n");
                        continue;
                    } 
                }

                if (--nready <= 0){ // No more readable description
                    break; 
                }
            }
        }
    }
}
