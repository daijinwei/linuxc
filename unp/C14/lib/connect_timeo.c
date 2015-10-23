#include "connect_timeo.h"

void str_cli(FILE *fp, SOCKETFD socketfd)
{
	char buf[BUF_SIZE];
	int n;
	char sendline[BUF_SIZE], recvline[BUF_SIZE];

	printf("~~~~~~* Please input the message *~~~~~~\n");
	while(fgets(sendline, BUF_SIZE, fp) != NULL) {
		n = write(socketfd, sendline, BUF_SIZE );	
		if (n < 0) {
			handle_error("write no  message");
		}

		if (0 == read(socketfd, recvline, BUF_SIZE)) {
			handle_error("read message failed");
		}

		fputs(recvline, stdout);
		printf("~~~~~~* Display the message *~~~~~~\n");
	}
}

static void
connect_alarm(int signo){
    if(SIGALRM == signo) {
        return; 
    }
}

int 
connect_timeo(int sockfd, const struct sockaddr *addr, socklen_t len, int timeout)
{
    int n;
    typedef void (*sighandler_t)(int);
    sighandler_t    sigfunc;

    if((sigfunc = signal(SIGALRM, connect_alarm)) != SIG_ERR) {
        handle_msg("Install the signal func connect_alarm is failed"); 
    }

    if(0 != alarm(timeout)){
        handle_msg("The alarm is allready set"); 
    }

	if(-1 == (n = connect(sockfd, addr, len))){
        close(sockfd);
		handle_error("connect socket failed\n");
	}

    alarm(0);                       // Trun off the alarm
    signal(SIGALRM, sigfunc);       // Restore previous signal handler 

    return n;
}
