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

#define MAX_LEN 128

void do_line(const char *cmd){
    printf("%s\n", cmd);
}

int main(int argc, char *argv[])
{
    char line[MAX_LEN];
    while(fgets(line, MAX_LEN, stdin) != NULL){
        do_line(line);
    }
    exit(0);
}
