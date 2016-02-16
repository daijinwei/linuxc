#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

unsigned long
ip2long(const char *addr)
{
    struct in_addr sa;
    if (NULL == addr) {
        return 0;
    }

    // Check ip invalid or not.
    if (1 != inet_pton(AF_INET, addr, &sa)){
        return 0;
    }
    unsigned char a, b, c, d;
    sscanf(addr, "%hhu.%hhu.%hhu.%hhu", &a, &b, &c, &d);
    return ((a << 24) | (b << 16) | (c << 8) | d);
}

int main(int argc, char *argv[])
{
    uint32_t long_ip;
    if ( 2 > argc) {
        exit(EXIT_FAILURE);
    }
    long_ip = ip2long(argv[1]);

    if (0 != long_ip) {
        printf("long ip is %u\n", long_ip);
    } else {
        printf("Convert long ip is %u is error\n", long_ip);
    }
    return 0;
}
