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

void server(int readfd, int writefd);

void server(int readfd, int writefd){
    int fd;
    ssize_t n;
    char buffer[BUFFER_SIZE];

    printf("Server 1\n");
    /* Read pathname from IPC channel */
    if((n = read(readfd, buffer, BUFFER_SIZE)) <= 0){
        printf("Server read file path failed\n");
        exit(EXIT_FAILURE);
    }
    // no '\n'
    buffer[n] = '\0';

    printf("Server 2\n");
    if((fd = open(buffer, O_RDONLY)) < 0){
        snprintf(buffer + n,sizeof(buffer) -n, ": Can't open, %s\n", strerror(errno));   
        n = strlen(buffer);
        if(-1 == write(writefd, buffer, n)){
            printf("write file path failed\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Server 3\n");
        while((n = read(fd, buffer, BUFFER_SIZE))){
            if(-1 == write(writefd, buffer, n)){
                printf("write file path failed\n");
                exit(EXIT_FAILURE);
            }
        }
        printf("\n");
        close(fd);
    }
} 

int main()
{
    int readfd, writefd;
    if((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)){
        printf("create a fifo1 failed\n");
        exit(1);
    }

    if((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)){
        printf("create a fifo1 failed\n");
        exit(1);
    }

    if((readfd = open(FIFO1, O_RDONLY)) < 0){
        printf("read FIFO1 failed\n");
        exit(1);
    }
    if((writefd = open(FIFO2, O_WRONLY)) < 0){
        printf("read FIFO2 failed\n");
        exit(1);
    }

    server(readfd, writefd);
    exit(0);
}
