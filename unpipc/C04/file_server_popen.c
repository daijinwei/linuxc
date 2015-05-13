/**
 * Copyright (c) 2015, project
 * File Name: file_server_popen.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-13
 * Modified: 2015-05-13
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_SIZE 1024

int main()
{
    int length;
    char buffer[BUFFER_SIZE];
    char command[MAX_SIZE];
    FILE *fp = NULL;
    if((fgets(buffer, BUFFER_SIZE, stdin)) == NULL){
        printf("fgets message faied\n");
    }
    length = strlen(buffer);
    if(buffer[length - 1] == '\n')
        length--;

    snprintf(command, sizeof(command), "cat %s", buffer);

    if((fp = popen(command, "r")) == NULL){
        printf("popen failed\n");
    }
    while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
        fputs(buffer, stdout);
    }
    pclose(fp);
    exit(0);
}
