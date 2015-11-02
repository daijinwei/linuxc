#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

volatile sig_atomic_t quitflag;     

void
pr_mask(const char *str)
{
    sigset_t    old;
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;                         // Backup the errno
    if (-1 == sigprocmask(0, NULL, &sigset)){   // if set is null, return signal mask form sigset
        printf("sigprocmask error\n"); 
    }

    printf("%s\t", str);
    if (sigismember(&sigset, SIGINT))   printf("SIGINT\t");
    if (sigismember(&sigset, SIGQUIT))   printf("SIGQUIT\t");
    if (sigismember(&sigset, SIGUSR1))   printf("SIGUSR1\t");
    if (sigismember(&sigset, SIGALRM))   printf("SIGALRM\t");
    printf("\n");
    errno = errno_save;         // Restore the errno
}

static void
sig_int(int signo)
{
    if (SIGINT == signo) {
        printf("\ninterrupt\n");    
    } else if (SIGQUIT == signo){
        quitflag = 1;     
    }
}

int main(int argc, char *argv[])
{
    sigset_t newmask, oldmask, zeromask;
    pr_mask("Process start");

    if (SIG_ERR == signal(SIGINT, sig_int)){
        printf("signal(SIGINT) error\n");    
    }

    if (SIG_ERR == signal(SIGQUIT, sig_int)){
        printf("signal(SIGQUIT) error\n");    
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    // Block SIGQUIT and save the current signal mask
    if (-1 == sigprocmask(SIG_BLOCK, &newmask, &oldmask)){
        printf("SIGQUIT BLOCK error"); 
    }
    
    pr_mask("in critical region: ");

    while (0 == quitflag){
        if (-1 != sigsuspend(&zeromask)){ 
            printf("Suspend is failed\n");
        }
    }

    pr_mask("After return from the sigsuspend: ");

    // Reset the SIGQUIT, unblock the SIGQUIT
    if (-1 == sigprocmask(SIG_SETMASK, &oldmask, NULL)){
        printf("Unblock SIGINT failed\n"); 
    }

    // And contiuing the processing
    pr_mask("process exit");
    exit(0);
}
