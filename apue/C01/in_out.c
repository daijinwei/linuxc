/**
 * Copyright (c) 2015, project
 * File Name: in_out.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-11
 * Modified: 2015-05-11
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFSIZE 4096

int main()
{
    int n;
    char buf[BUFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0){
        if(write(STDOUT_FILENO, buf, n) != n){
            printf("write error\n");
        }
    }
    if(n < 0){
        printf("write error\n");
    }
    exit(0);
}

