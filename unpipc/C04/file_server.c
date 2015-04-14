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

#define BUFFER_SIZE     512

void client(int readfd, int writefd);
void server(int readfd, int writefd);

void client(int readfd, int writefd){
    char buffer[BUFFER_SIZE];
    int length, n;
    memset(buffer, 0 , BUFFER_SIZE);
    if(NULL == fgets(buffer, BUFFER_SIZE,stdin)){
        printf("Read file_path from stdin failed\n");
        exit(EXIT_FAILURE);
    }
    length = strlen(buffer);
    if(-1 == write(writefd, buffer, length)){
        printf("write file path failed\n");
        exit(EXIT_FAILURE);
    }
    
    while(n = read(readfd, buffer, BUFFER_SIZE)){
        fprintf(stdout,"%s", buffer); 
    }
}

void server(int readfd, int writefd){

}

int main()
{
    int ret;

    // Define two pipe
    int pipe1[2];
    int pipe2[2];

    // Open 2 pipe
    ret = pipe(pipe1);
    if(-1 == ret){
        printf("Create pipe1 failed\n");
        exit(EXIT_FAILURE);
    }
    ret = pipe(pipe2);
    if(-1 == ret){
        printf("Create pipe2 failed\n");
        exit(EXIT_FAILURE);
    }
    if(0 == fork()){    // Child process for server
        if(close(pipe1[1]) < 0){
            printf("Close pipe1 write failed\n");
            exit(EXIT_FAILURE);
        }
        if(close(pipe2[0])){
            printf("Close pipe2 read failed\n");
            exit(EXIT_FAILURE);
        }
        server(pipe1[0], pipe2[1]);
    }else{              // Parent process for client
        if(close(pipe1[0]) < 0){
            printf("Close pipe1 read failed\n");
            exit(EXIT_FAILURE);
        }
        if(close(pipe2[1])){
            printf("Close pipe2 write failed\n");
            exit(EXIT_FAILURE);
        }
        client(pipe2[0], pipe1[1]);
    }
}
