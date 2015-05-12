/**
 * Copyright (c) 2015, project
 * File Name: get_init_fork.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-04
 * Modified: 2015-05-04
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0) {
        printf("First fork error\n");
    }else if(0 == pid){             // First child
        if((pid = fork()) < 0){
            printf("Second fork error\n");
        }else if(pid > 0){          // parent from seconde fork == first child
            printf("First child, pid = %d\n", getpid());
            exit(0);
        }
        // Second second
        sleep(2);
        printf("second child, pid = %d\n", getpid());
        printf("second child, parent pid = %d\n", getppid());
        exit(0);
    }

    printf("First parent, pid = %d\n", getpid());
    if(waitpid(pid, NULL, 0) != pid){       // Wait first child
        printf("waitpid error\n");
    }
    exit(0);
}
