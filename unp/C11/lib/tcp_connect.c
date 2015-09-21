#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50

#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)

int tcp_connect(const char *host, const char *serv)
{
    int sockfd, n;

    struct addrinfo host_init, *res, *ressave;
    bzero(&host_init, sizeof(struct addrinfo));
    host_init.ai_family = AF_UNSPEC; 
    host_init.ai_socktype = SOCK_STREAM;

    if ( 0 != (n = getaddrinfo(host, serv, &host_init, &res))){
        handle_error("getaddrinfo failed\n"); 
    }
    ressave = res;
    
    for ( NULL != res; res = res->ai_next;) {
        if ( 0 > (sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
            continue;               // Ignore this one 
        }
        
        if( 0 == connect(sockfd, res->ai_addr, res->ai_addrlen)) {
            break;                  // Connect success 
        }
        close(sockfd);
    }

    if (NULL == res){
        handle_error("tcp connect error\n");
    }
    freeaddrinfo(ressave);
    return sockfd;
}

int main(int argc, char *argv[])
{
    //const char *host = "www.baidu.com";
    tcp_connect("linux", "daytime");
}
