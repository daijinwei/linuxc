/**
 * Copyright (c) 2015, project
 * File Name: my_fork.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-28
 * Modified: 2015-04-28
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 0;
int main()
{
    int i = 0;
    for(i; i < 2; ++i){
        if(0 == fork()){
            execl("/bin/bash", "bash", "-cx","ls", NULL);
            exit(0);
        }
    }

    //printf("glob\t%d\n", glob);
    printf("hello world\n");
}
