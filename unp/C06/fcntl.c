#include <stdio.h>
#include <fcntl.h>

#define     OK          0
#define     ERROR       -1

/* Set a socket as nonbloking*/
int set_nonblocking(int fd)
{
    int flags;
    if ( (flags = fcntl(fd, F_GETFL, 0)) < 0){
        return ERROR;
        printf("F_GETFL error\n"); 
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0){
        return ERROR;
        printf("F_SETFL error\n"); 
    }
    return OK;
}

int main(int argc, char *argv[])
{
    int fd; // as a socket
    int ret = 0;
    ret = set_nonblocking(fd);    
    if (-1 == ret) {
        printf("Set nonblocking failed\n"); 
    }
}
