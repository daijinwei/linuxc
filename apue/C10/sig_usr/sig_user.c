#include <stdio.h>
#include <unistd.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

static void sig_usr(int signo)
{
    if (SIGUSR1 == signo){
        printf("Received the SIGUSR1\n"); 
    }else if (SIGUSR2 == signo){
        printf("Received the SIGUSR2\n"); 
    }else{
        printf("No capture the signal\n"); 
    }
    return;
}

int main(int argc, char *argv[])
{
    sighandler_t handler;
    if(SIG_ERR == (handler = signal(SIGUSR1, sig_usr))){
        printf("Can not capture the SIGUSR1\n"); 
    }

    if(SIG_ERR == (handler = signal(SIGUSR2, sig_usr))){
        printf("Can not capture the SIGUSR2\n"); 
    }

    for( ; ; ) {
        pause(); 
    }
}
