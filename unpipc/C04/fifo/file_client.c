/**
 * Copyright (c) 2015, project
 * File Name: file_server.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-14
 * Modified: 2015-04-14
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // For fork
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"

#define BUFFER_SIZE     512

void client(int readfd, int writefd);

void client(int readfd, int writefd){
    printf("client 1\n");
    char buffer[BUFFER_SIZE];
    int length, n;
    memset(buffer, 0 , BUFFER_SIZE);
    if(NULL == fgets(buffer, BUFFER_SIZE,stdin)){
        printf("Read file_path from stdin failed\n");
        exit(EXIT_FAILURE);
    }
    printf("client 2\n");
    length = strlen(buffer);
    // The buffer no '\n'
    if(buffer[length - 1] == '\n')
        length--;

    if(-1 == write(writefd, buffer, length)){
        printf("write file path failed\n");
        exit(EXIT_FAILURE);
    }
    printf("client 3\n");
    
    while(n = read(readfd, buffer, BUFFER_SIZE)){
        fprintf(stdout,"%s", buffer); 
    }
    printf("client 4\n");
}

int main()
{
    printf("1\n");
    int readfd, writefd;             
    // half dupex, server FIFO1 read, client FIFO1 write
    if((writefd = open(FIFO1, O_WRONLY)) < 0){
        printf("read FIFO1 failed\n");
        exit(1);                     
    }                                
    printf("2\n");
    if((readfd = open(FIFO2, O_RDONLY)) < 0){
        printf("read FIFO2 failed\n");                                                                 
        exit(1);                     
    }                                

    printf("3\n");
    client(readfd, writefd);         
    close(readfd);
    close(writefd);
    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);     
}
