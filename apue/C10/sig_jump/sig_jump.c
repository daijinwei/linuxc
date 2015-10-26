#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

static sigjmp_buf               jmpbuf;
static volatile sig_atomic_t    canjump;

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
sig_alarm(int signo)
{
    pr_mask("sig_alarm");
}

static void
sig_usr1(int signo)
{
    time_t start_time;
    if (canjump == 0) return;   // unexpected signal, ignore

    pr_mask("start sig_usr1: ");
    alarm(3);

    // Pause 5 sec
    start_time = time(NULL);
    for ( ; ; ){
        if (time(NULL) > start_time + 5){
            break; 
        } 
    }
    pr_mask("end sig_usr: ");
    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

int main(int argc, char *argv[])
{
    if (SIG_ERR == signal(SIGUSR1, sig_usr1)){
        printf("signal(SIGUSR1) failed\n"); 
    }

    if (SIG_ERR == signal(SIGALRM, sig_alarm)){
        printf("signal(SIGUSR1) failed\n"); 
    }

    // print signal mask 
    pr_mask("starting main: ");

    // Set sigsetjump
    if (sigsetjmp(jmpbuf, 1)){
        // print signal mask
        pr_mask("end main: ");
        exit(0);
    } 

    // sigsetjump sucess, set canump is non-zero, protect rule
    canjump = 1;

    // Wait signal
    for( ; ; ) {
        pause(); 
    }
}
