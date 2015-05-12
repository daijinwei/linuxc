/**
 * Copyright (c) 2015, project
 * File Name: my_wait.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-04
 * Modified: 2015-05-04
 * Description: 
 **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void pr_exit(int status)
{
    if(WIFEXITED(status)){
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    }

    else if(WIFSIGNALED(status)){
        printf("abnormal termination, exit status = %d%s\n", WTERMSIG(status), 
#ifdef  WCOREDUMP
            WCOREDUMP(status) ? "(core file generated)" : "");
#else 
            "");
#endif
    }
    else if(WIFSTOPPED(status)){
            printf("child stoped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main()
{
    pid_t pid;
    int status; 

    if((pid = fork()) < 0){
        printf("fork error\n");
    }else if(pid == 0){         // child
        exit(7);
    }

    if(wait(&status) != pid){
        printf("wait error\n");
    }
    pr_exit(status);

    
    if((pid = fork()) < 0){
        printf("fork error\n");
    }else if(pid == 0){         // child
        abort();                // generate SIGABORT
    }

    if(wait(&status) != pid){
        printf("wait error\n");
    }
    pr_exit(status);


    if((pid = fork()) < 0){
        printf("fork error\n");
    }else if(pid == 0){         // child
        status /= 0;                // generate SIGABORT
    }

    if(wait(&status) != pid){
        printf("wait error\n");
    }
    pr_exit(status);

}
