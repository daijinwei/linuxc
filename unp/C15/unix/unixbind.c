#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    int sockfd;
    socklen_t len;
    struct sockaddr_un addr1, addr2;
    if (2 != argc){
        printf("Usage: unixbind <pathname>\n");
        exit(1);
    }

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (-1 == sockfd){
        printf("unix socket failed\n");
        exit(1);
    }

    unlink(argv[1]);
    bzero(&addr1, sizeof(addr1));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
    if(-1 == bind(sockfd, (struct sockaddr *)&addr1, sizeof(struct sockaddr_un))){
        printf("bind socket failed, errno=%d\n", errno);
        exit(1);
    }

    len = sizeof(addr2);
    if (-1 == getsockname(sockfd, (struct sockaddr*)&addr2, &len)){
        printf("getsocknamefailed, Errno = %s\n", errno);
        exit(1);
    }

    printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
    exit(0);
}
