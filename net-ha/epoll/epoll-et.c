#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/epoll.h>

#define IPADDR  "0.0.0.0"
#define PORT	8090

#define MAXSIZE     1024
#define LISTENQ     5
#define FDSIZE      1000
#define EPOLLEVENTS 100

static void add_event(int epollfd, int fd, int state);

int socket_bind(const char *ip, int port){
    int listenfd;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error:");
        exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);
    
    if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1 ) {
        perror("bind listenfd error: ");
        exit(1);
    }
    return listenfd;
}

int set_nonblock(int fd)
{
    int old_flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, old_flags | O_NONBLOCK);
    return old_flags;
}

static void add_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    ev.events |= EPOLLET;
    set_nonblock(fd);
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    ev.events |= EPOLLET;
    set_nonblock(fd);
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void handle_accept(int epollfd, int listenfd){
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;

    clifd = accept(listenfd,  (struct sockaddr *)&cliaddr, &cliaddrlen);
    if ( clifd == -1 ) {
        perror("accept error");
    } else {
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
    
}

static void do_read(int epollfd,int fd,char *buf)
 {
     int nread;
     for (; ; ){
         nread = read(fd,buf,MAXSIZE);
         if (nread == -1)
         {
             perror("read error:");
             close(fd);
             delete_event(epollfd,fd,EPOLLIN);
         }
         else if (nread == 0)
         {
             fprintf(stderr,"client close.\n");
             close(fd);
             delete_event(epollfd,fd,EPOLLIN);
         }
         else
         {
             printf("read message is : %s", buf);
             //修改描述符对应的事件，由读改为写
             modify_event(epollfd,fd,EPOLLOUT);
         }
    }
 }

static void do_write(int epollfd,int fd,char *buf)
{
    int nwrite;
    nwrite = write(fd,buf,strlen(buf));
    if (nwrite == -1)
    {
        perror("write error:");
        close(fd);
        delete_event(epollfd,fd,EPOLLOUT);
    }
    else
        modify_event(epollfd,fd,EPOLLIN);
    memset(buf,0,MAXSIZE);
}


void handle_events(int epollfd, struct epoll_event *events, int num , int listenfd, char *buf){
     int i;
     int fd;
     for (i = 0; i < num; i++){
         fd = events[i].data.fd;
         if ((fd == listenfd) && (events[i].events & EPOLLIN)) {
			 handle_accept(epollfd, fd);
         } else if (events[i].events & EPOLLIN) {
			 do_read(epollfd,fd,buf);
         } else if (events[i].events & EPOLLOUT) {
             do_write(epollfd,fd,buf);
         }
     }
}
   
void * do_epoll(int listenfd) {
    int epollfd;
    int ret;
    char buf[MAXSIZE];
    struct epoll_event events[EPOLLEVENTS];
    
    epollfd = epoll_create(FDSIZE);
    add_event(epollfd, listenfd, EPOLLIN);
    for ( ; ; ) {
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    close(epollfd);
}


int main(int argc, char **argv){
    int listenfd;
    listenfd = socket_bind(IPADDR, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}
