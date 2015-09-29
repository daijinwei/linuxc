#include "tcp_listen.h"
#include "log.h"

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
    int listenfd, n;
    int backlog = LISTEN_BACKLOG;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags   = AI_PASSIVE;
    hints.ai_family  = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( 0!= (n = getaddrinfo(host, serv, &hints, &res))){
        LOG(ERROR, "tcp_listen %s %s failed, Error: %s\n", host, serv, gai_strerror(n));
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
    if ( 0 != listen(listenfd, backlog)) {
        LOG(ERROR, "listen failed\n");
    }

    if (NULL != addrlenp){
        *addrlenp = res->ai_addrlen ;
    }
    freeaddrinfo(ressave);
    return listenfd;
}
