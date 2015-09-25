#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50
#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)


typedef int SOCKETFD;

// The process usr select and shutdown to deal with mass of data.
void str_cli(FILE *fp, SOCKETFD socketfd)
{
	char buf[BUF_SIZE];
	int n;
    int maxfd;
    int ret;
    int stdineof;
	char sendline[BUF_SIZE], recvline[BUF_SIZE];

	printf("~~~~~~* Please input the message *~~~~~~\n");
    stdineof = 0;
    fd_set rset;
    FD_ZERO(&rset);
    for( ; ; ) {
        if(stdineof == 0){
            FD_SET(fileno(fp), &rset); 
        }
        FD_SET(fileno(fp), &rset);
        FD_SET(socketfd, &rset);
        maxfd = fileno(fp) >  socketfd?fileno(fp):socketfd;
        ret = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(-1 == ret) { // Recvie the RST, set errno
			handle_error("Select error");
        }

        if(0 == ret) {  // Recive FIN
			continue;
        }

        if(FD_ISSET(socketfd, &rset)) {
		    if (0 == read(socketfd, buf, BUF_SIZE)) {
                if(1 == stdineof) { // Normal terminate
                    return; 
                }else{
			        handle_error("read message failed");
                }
		    }

            if(write(fileno(stdout), buf, n) < 0) { // stdout must convert to fileno(stdout)
                printf("dispay error\n"); 
            }
		    printf("~~~~~~* Display the message *~~~~~~\n");
        }

        if(FD_ISSET(fileno(fp), &rset)){
	        if( 0 == ( n = (read(fileno(fp), buf, BUF_SIZE)))) {    // should use readn, operate the buf
                stdineof = 1; 
                if(-1 == shutdown(socketfd, SHUT_WR)){  // Send FIN
                    printf("Send FIN failed\n"); 
                } 
                FD_CLR(fileno(fp), &rset);
                continue;
            }else{
		        n = write(socketfd, sendline, BUF_SIZE );	
		        if (n < 0) {
			        handle_error("write no  message");
		        }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int ret;
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

    if(0 >=(ret = inet_pton(AF_INET, argv[1] ,&server_addr.sin_addr))){
        if (0== ret )
		    handle_error("the  presentation address is  not right\n");
        if(-1 == ret){
		    handle_error("covert error\n");
        }
    }
	
	if(-1 == connect(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr))){
		handle_error("connect socket failed\n");
	}

	str_cli(stdin, sockfd);
	exit(0);
}