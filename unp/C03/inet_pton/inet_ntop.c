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
    if ((NULL == addrptr) || (NULL == strptr)) return 0;

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

/**
 * Convert network address to presentation address
 * famili: AF_INET
 * strptr: presention address, for example, 192.168.1.1
 * addrptr: network address, for example, 1010101l 01010101 01010101 01010123 
 * len: the strptr buf size
 */
const char *
my_inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
    //if ((NULL == addrptr) || (NULL == strptr)) return NULL;

    const u_char *p = (const u_char *)addrptr;
    if (AF_INET == family) { 
        char tmp[INET_ADDRSTRLEN];
        snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
        if (len < strlen(tmp)) {
            errno = ENOSPC;
            return NULL;
        }
        strcpy(strptr, tmp);
        return strptr;
    }
    errno = EAFNOSUPPORT;
    return NULL;
}

int main(int argc, char *argv[])
{
    char numeric_buf[64];
    char presentation_buf[64];
    const char *p = NULL;
    bzero(numeric_buf, sizeof(numeric_buf));
    if (0 >= my_inet_pton(AF_INET, argv[1], (void *)numeric_buf)){
        perror("Convert presentation address to network address failed\n");
    }
    printf("network addr string: %d\n", numeric_buf);

    if (NULL == (p = my_inet_ntop(AF_INET, numeric_buf, presentation_buf, 64))){
        perror("Convert netword address to presentation address failed\n");
    }
    printf("presentation: %s\n", p);
    return 0;
}
