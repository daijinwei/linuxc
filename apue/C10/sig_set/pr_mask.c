#include <stdio.h>
#include <signal.h>
#include <errno.h>

void
pr_mask(const char *str)
{
    sigset_t    old;
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;         // Backup the errno
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT); 
    sigaddset(&sigset, SIGQUIT); 
    // if (sigprocmask(SIG_BLOCK, &sigset, &old) < 0)

    //if (-1 == sigprocmask(0, NULL, &sigset)){
    //    printf("sigprocmask error\n"); 
    //}

    printf("%s\n", str);

    if (sigismember(&sigset, SIGINT))   printf("SIGINT\t");
    if (sigismember(&sigset, SIGQUIT))   printf("SIGQUIT\t");
    if (sigismember(&sigset, SIGUSR1))   printf("SIGUSR1\t");
    if (sigismember(&sigset, SIGALRM))   printf("SIGALRM\n");

    printf("\n");
    errno = errno_save;         // Restore the errno
}

int main()
{
    pr_mask("david");
}
