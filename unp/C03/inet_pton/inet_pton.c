#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * Convert present address to network address
 * famili: AF_INET
 * strptr: presention address, for example, 192.168.1.1
 * addrptr: network address, for example, 1010101l 01010101 01010101 01010123 
 */
int 
my_inet_pton(int family, const char *strptr, void *addrptr)
{
    if ((NULL == strptr) || (NULL == addrptr)) return 0;
    if (AF_INET == family){
        struct in_addr inet_val;

        if (1 == inet_aton(strptr, &inet_val)){
            memcpy(addrptr, &inet_val, sizeof(struct in_addr));
            return 1;
        }
        return 0;
    } 
    errno = EAFNOSUPPORT;
    return -1;
}

int main(int argc, char *argv[])
{
    char buf[64];
    bzero(buf, sizeof(buf));
    if (0 >= my_inet_pton(AF_INET, argv[1], (void *)buf)){
        printf("Conver error\n"); 
    }
    printf("network addr string: %d\n", buf);
    return 0;
}
