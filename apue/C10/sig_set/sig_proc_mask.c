#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static
void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR){
        printf("can't reset SIGQUIT\n");
    }
}

int main()
{
    sigset_t    newmask, oldmask, pendmask;
    if(signal(SIGQUIT, sig_quit) == SIG_ERR){
        printf("Signal SIGQUIT error\n"); 
    }

    /**
     * Block SIGQUIT and save current signal mask
     **/
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask)){
        printf("sigprocmask set SIG_BLOCK failed\n"); 
    }

    sleep(5);           // SIGQUIT here will remain pending
    if (sigpending(&pendmask) < 0){
        printf("sigpending error\n"); 
    }

    // SIG_BLOCK must be pending
    if(sigismember(&pendmask, SIGQUIT)){
        printf("\nSIGQUIT pending\n");         
    }

    // Reset the signal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        printf("SIG_SETMASK errro\n"); 
    }

    printf("SIGQUIT unblocked\n");
    sleep(5);
    exit(0);
}
