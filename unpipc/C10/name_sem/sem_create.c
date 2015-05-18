/**
 * Copyright (c) 2015, project
 * File Name: sem_create.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-18
 * Modified: 2015-05-18
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>


#define  FILE_MODE 0755
#define  SEM    "daijinwei"

int main(int argc, char *argv[])
{
    int c, flags;
    sem_t * sem = NULL;
    uint32_t value;
    char name[128];
    
    flags = O_RDWR | O_CREAT;
    value = 1;
    memset(name, 0, sizeof(name));
    sprintf(name, SEM);
    while(-1 != (c = getopt(argc, argv, "ei:"))){
        switch (c){
            case 'e':
                flags |= O_EXCL;
                break;
            case 'i':
                value = atoi(optarg);
                break;
        }
    }

    if(optind != argc -1){
        printf("Usage: semcreate [-e] [-i initalvalue] <name>");
    }
    if(SEM_FAILED ==(sem = sem_open(argv[optind], flags, FILE_MODE, value))){
        printf("sem_open failed\n");
    }
    if(-1 == sem_close(sem)){
        printf("sem_close failed\n");
    }
    exit(0);
}
