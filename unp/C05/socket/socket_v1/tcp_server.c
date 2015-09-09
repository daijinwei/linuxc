#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50
#define handle_error(msg)	\
	do{ perror(msg); exit(EXIT_FAILURE);}while(0)


typedef int SOCKETFD;

void str_echo(SOCKETFD socketfd)
{
	char buf[BUF_SIZE];
	int n;
again:
	while((n = read(socketfd, buf, sizeof(buf))) > 0){
		n = write(socketfd, buf, n);	
	}
    if (n < 0 && errno == EINTR) {
        goto again ;
    }
	else if (n < 0 ) {
		handle_error("read message failed");
	}
}

int main()
{
	int	listen_fd, connect_fd;
	int port = 9877;	
	pid_t	pid;
	socklen_t	clientlen;
	struct sockaddr_in 	client_addr, server_addr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listen_fd) {
		handle_error("create socket failed\n");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	if(-1 == bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
		handle_error("bind socket failed\n");
	}

	if (-1 == listen(listen_fd, LISTEN_BACKLOG)){
		handle_error("listen socket failed\n");
	}

	for (;;) {
		clientlen = sizeof(client_addr);
		if (-1 == (connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &clientlen))){
			handle_error("accept message failed\n");
		}

		if(0 == (pid = fork())) {
			close(listen_fd);	
			str_echo(connect_fd);
			exit(0);
		}
		close(connect_fd);
	}
}
