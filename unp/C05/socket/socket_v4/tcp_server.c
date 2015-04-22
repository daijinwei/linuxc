/**
 * Copyright: <David daijiwei41@gmail.com>
 * Created:   2015-04-22
 * Modify:    2015-04-22
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>

#define BUF_SIZE	1024
#define LISTEN_BACKLOG	50

#define MAX_EVENTS 10

#define handle_error(msg)	\
	do{ 					\
		perror(msg); 		\
		exit(EXIT_FAILURE);	\
	}while(0)


typedef int SOCKETFD;

void str_echo(SOCKETFD socketfd)
{
	char buf[BUF_SIZE];
	int n;
	while((n = read(socketfd, buf, sizeof(buf))) > 0){
		n = write(socketfd, buf, n);	
		if (n < 0) {
			handle_error("write no  message");
		}
	}

	if (n < 0 ) {
		handle_error("read message failed");
	}
}

void sig_chld(int signo){
	pid_t	pid;
	int		stat;

	while((pid = waitpid(-1,&stat, WNOHANG)) > 0) 
		printf("child %d terminated\n", pid);
	return;
}


void set_noblocking(int fd){
  int ret;
  ret = fcntl(fd, F_GETFL);
  if(ret < 0){
    handle_error("get flil ds filed\n");
    exit(EXIT_FAILURE);
  }
  ret = ret | O_NONBLOCK;
  if(fcntl(fd, F_SETFL, ret) < 0){
    handle_error("set nonblocking filed\n");
    exit(EXIT_FAILURE);
  }
}

int main()
{
	int	listen_fd, connect_fd;
	int port = 8080;	
	pid_t	pid;
	socklen_t	clientlen;
	struct sockaddr_in 	client_addr, server_addr;
  // epoll
  int epollfd, nfds, i;
  struct epoll_event ev, events[MAX_EVENTS];

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

  epollfd = epoll_create(MAX_EVENTS); 
  if(epollfd < 0) {
    handle_error("create epoll failed\n");
    exit(EXIT_FAILURE);
  }
  ev.data.fd = listen_fd; 
  ev.events = EPOLLIN;
  if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_fd, &ev)){
    handle_error("Epoll ctl add listen fd failed\n");
    exit(EXIT_FAILURE);
  }

	for (; ;) {
    nfds = epoll_wait(epollfd, events, 20, 50);
    if(-1 == nfds){
      handle_error("Epoll ctl add listen fd failed\n");
      exit(EXIT_FAILURE);
      
    }
    for(i = 0; i < nfds; ++i){
      if(events[i].data.fd == listen_fd) {
		    clientlen = sizeof(client_addr);
		    if ((connect_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &clientlen)) < 0){
				  handle_error("accept message failed\n");
		    }
        ev.data.fd = connect_fd;
        set_noblocking(connect_fd);
        if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_fd, &ev)){
          handle_error("Epoll ctl add listen fd failed\n");
        }
            
      }
      else if(events[i].events | EPOLLIN){
        // read       

        ev.events= EPOLLOUT | EPOLLET;
        if(-1 == epoll_ctl(epollfd, EPOLL_CTL_MOD, listen_fd, &ev)){
          handle_error("Epoll ctl add listen fd failed\n");
        }


      }
      else if(events[i].events | EPOLLOUT){
        // send
        ev.events= EPOLLIN | EPOLLET;
        if(-1 == epoll_ctl(epollfd, EPOLL_CTL_MOD, listen_fd, &ev)){
          handle_error("Epoll ctl add listen fd failed\n");
        }
      }

    }

		close(connect_fd);

	}
}
