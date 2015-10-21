#include "connect_timeo.h"
int main(int argc, char *argv[])
{
    int ret;
	if (3 != argc) {
		handle_error("Usage: tcp_client <IPaddress> <port>");
	}

	int	sockfd;
	int server_port = atoi(argv[2]);	
	socklen_t	clientlen;
	struct sockaddr_in 	client_addr, server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		handle_error("create socket failed\n");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);

    if(0 >=(ret = inet_pton(AF_INET, argv[1] ,&server_addr.sin_addr))){
        if (0== ret )
		    handle_error("the  presentation address is  not right\n");
        if(-1 == ret){
		    handle_error("covert error\n");
        }
    }
	
    connect_timeo(sockfd, (const struct sockaddr*)&server_addr, sizeof(server_addr), 3);

	str_cli(stdin, sockfd);
	exit(0);
}
