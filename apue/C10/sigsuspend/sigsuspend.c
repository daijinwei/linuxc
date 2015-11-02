#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

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
    pr_mask("\nin sig_int: ");
}

int main(int argc, char *argv[])
{
    sigset_t newmask, oldmask, waitmask;
    pr_mask("Process start");

    if (SIG_ERR == signal(SIGINT, sig_int)){
        printf("signal(SIGINT) error\n");    
    }

    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    // Block SIGINT and save the current signal mask
    if (-1 == sigprocmask(SIG_BLOCK, &newmask, &oldmask)){
        printf("SIGINT BLOCK error"); 
    }
    
    pr_mask("in critical region: ");

    // Pause, allowing all signals except SIRUSR1
    if (-1 != sigsuspend(&waitmask)){ 
        printf("Suspend is failed\n");
    }

    pr_mask("After return from the sigsuspend: ");

    if (-1 == sigprocmask(SIG_SETMASK, &oldmask, NULL)){
        printf("Unblock SIGINT failed\n"); 
    }

    // And contiuing the processing
    pr_mask("process exit");
    exit(0);
}
