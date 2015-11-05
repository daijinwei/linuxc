#include <stdio.h>
#include <stdlib.h>
#include "system_signal.h"


static void
sig_int(int signo)
{
    printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
    printf("caught SIGCHLD\n");
}

int main(int argc, char *argv[])
{
    if (SIG_ERR == signal(SIGINT, sig_int)){
        printf("signal(SIGINT) is failed\n"); 
    }

    if (SIG_ERR == signal(SIGCHLD, sig_chld)){
        printf("signal(SIGCHLD) is failed\n"); 
    }

    if (system_signal("/bin/ed") < 0) {
        printf("system(bin/ed) is error"); 
        exit(1);
    }
    exit(0);
}
