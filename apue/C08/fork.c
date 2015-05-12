/**
 * Copyright (c) 2015, project
 * File Name: fork.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-27
 * Modified: 2015-04-27
 * Description: 
 **/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int glob = 6;
char buf[] = "A write to stdout\n";

int main(){
    int var;
    pid_t pid;
    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1)!= sizeof(buf) - 1){
       printf("write error\n"); 
    }

    printf("before fork\n");
    if((pid = fork()) < 0) {
       printf("fork error\n"); 
    }else if(pid == 0){
        glob++;
        var++;
        execl("/bin/bash", "bash", "-cx", "ls", NULL);
    }else{
        sleep(2);
    }

    printf("pid =%d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
