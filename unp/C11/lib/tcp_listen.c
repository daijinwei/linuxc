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

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
    int listenfd, n;
    int backlog = 1024;
    struct addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags   = AI_PASSIVE;
    hints.ai_family  = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( 0!= (n = getaddrinfo(host, serv, &hints, &res))){
        handle_error("tcp_listen error for: %s %s, Error:%s\n", host, serv, gai_strerror(n));  
    }

    ressave = res;
    for (res; NULL != res; res = res->ai_next) {
        if ( 0 > (listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))) {
            continue; 
        }
        if ( (n = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0 ) {
        
        }

        if ( 0 == bind(listenfd, res->ai_addr, res->ai_addrlen)){
            break; 
        }
        close(listenfd);
    }
    listen(listenfd, backlog);

}

int main(int argc, char *argv[])
{
    //const char *host = "www.baidu.com";
    tcp_listen("linux", "daytime", );
}
