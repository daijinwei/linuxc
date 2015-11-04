#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

/* Version without signal handing */
int system_nosignal(const char *cmdstring)
{
    pid_t   pid;
    int     status;
    if (NULL == cmdstring){
        return 1;               // Always a command processor with UNIX 
    }

    pid = fork();
    if (pid < 0){
        status = -1;            // Probaly out of process
    } else if (pid == 0) {
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
}

int main()
{
    system_nosignal("ls -l");
}
