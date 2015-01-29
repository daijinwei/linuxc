/*
 * =====================================================================================
 *
 *       Filename:  getaddrinfo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/23/2014 09:15:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

void host_serv(int listen_port) 
{
	char port[sizeof("65535") + 1];
	struct addrinfo hints, *result, *result0;
	memset(&hints, 0 ,sizeof(hints));
	hints.ai_family	= AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	sprintf(port, "%d", listen_port);

	int ret;
	ret = getaddrinfo(NULL, port, &hints, &result0);
	if ( 0 != ret) {
		printf("getaddrinfo failed\n");
	}

	for(result = result0; result; result->ai_next) {
		if(result->ai_family == AF_INET || result->ai_next == NULL) {
			printf("socket family %d\n", result->ai_family);	
			//printf("%d\n", (((struct sockaddr_in *)(result->ai_addr))->sin_addr).s_addr);
			break;
		}
	}

}

int main()
{
	int port = 999;
	host_serv(port);
	
}
