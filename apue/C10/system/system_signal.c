#include "system_nosignal.h"

/* Version without signal handing */
int system_signal(const char *cmdstring)
{
    pid_t   pid;
    int     status;
    struct sigaction    ignore, saveint, savequit;
    sigset_t            childmask, savemask;

    if (NULL == cmdstring){
        return 1;               // Always a command processor with UNIX 
    }

    ignore.sa_handler = SIG_IGN;            // ignore SIGINT and SIGQUIT
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (0 > sigaction(SIGINT, &ignore, &saveint)) {
        printf("sigaction(SIGINT) failed"); 
    }

    if (0 > sigaction(SIGQUIT, &ignore, &savequit)) {
        printf("sigaction(SIGQUIT) failed"); 
    }

    // Block SIGCHLD
    sigemptyset(&childmask);
    sigaddset(&childmask, SIGQUIT);
    if (0 > sigprocmask(SIG_BLOCK, &childmask, &savemask)){
        return -1; 
    }

    pid = fork();
    if (pid < 0){
        status = -1;            // Probaly out of process
    } else if (pid == 0) {
        // Reset signal mask
        if (0 > sigaction(SIGINT, &saveint, NULL)) {
            printf("sigaction(SIGINT) failed"); 
        }

        if (0 > sigaction(SIGQUIT, &savequit, &savequit)) {
            printf("sigaction(SIGQUIT) failed"); 
        }

        if (0 > sigprocmask(SIG_SETMASK, &childmask, &savemask)){
            return -1; 
        }


        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0); 
        _exit(127);
    }else{
        while( waitpid(pid, &status, 0) < 0) {
            if (errno == EINTR){
                status = -1;    // Error other than EINTR from waitpid
                break;
            }
        }
    }


    // restore previous signal
    if (0 > sigaction(SIGINT, &saveint, NULL)) {
        printf("sigaction(SIGINT) failed"); 
    }

    if (0 > sigaction(SIGQUIT, &savequit, &savequit)) {
        printf("sigaction(SIGQUIT) failed"); 
    }

    if (0 > sigprocmask(SIG_SETMASK, &childmask, &savemask)){
        return -1; 
    }

    return status;
}
