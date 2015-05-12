/**
 * Copyright (c) 2015, project
 * File Name: do_cmd.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-29
 * Modified: 2015-04-29
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define MAX_LEN 128

jmp_buf env;
int count = 0;

void do_line(const char *cmd){
    if(cmd != NULL){
        count++;
    }else{
        count--;
    }
    printf("count\t%d\n",count);
    if(count > 10){
        longjmp(env, 1);
    }
}

int main(int argc, char *argv[]){
    char line[MAX_LEN];
    if(setjmp(env) != 0){
        printf("error\n");
    }
    while(fgets(line, MAX_LEN, stdin) != NULL){
        do_line(line);
    }
    exit(0);
}
