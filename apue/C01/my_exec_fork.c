/*************************************************************************
	> File Name: my_exec_fork.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 May 2015 11:02:57 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_BUF 4096

int main()
{
    pid_t pid;
    int status;
    char buf[MAX_BUF];
    while(fgets(buf, MAX_BUF, stdin) != NULL){  // get a line string
        if(buf[strlen(buf) - 1] == '\n')
           buf[strlen(buf) - 1] = 0;

        if((pid = fork()) < 0) {
            printf("fork error\n");
        }else if( 0 == pid){
            execlp(buf, buf, (char *)0);
           // printf("could't execute: %s", buf);
            exit(127);
        }

        if(waitpid(pid, &status, 0) < 0){
            printf("waitpid error\n");
        }

        printf("%% ");
    }
    return 0;
}
