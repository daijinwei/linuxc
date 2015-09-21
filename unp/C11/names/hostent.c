#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50

#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)


int main(int argc, char *argv[])
{
    char *hostname = NULL;
    char *addr = NULL;
    char **pptr = NULL;
    char str[INET_ADDRSTRLEN];
    if (argc < 2){
        printf("Usage: ./hostent <host>\n"); 
        exit(EXIT_FAILURE);
    }
    hostname = argv[1];
    struct hostent *hptr = NULL;
    if ( NULL == (hptr = gethostbyname(hostname))) {
        handle_error("gethostbyname failed\n");
    }
    printf("official name: %s\n", hptr->h_name);

    for (pptr = hptr->h_aliases; NULL != *pptr; pptr++) {
        printf("aliases name: %s\n", *pptr);
    }

    switch (hptr->h_addrtype) {
        case AF_INET: 
            pptr = hptr->h_addr_list;
            for ( ; NULL != *pptr; pptr++){
                addr = inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
                if (NULL != addr) {
                    printf("address: %s\n", addr);
                }
            }
            break;
        default: 
            printf("Unkown hostname\n");
            break;
    }
}
