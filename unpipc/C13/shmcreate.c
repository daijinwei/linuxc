/**
 * Copyright (c) 2015, project
 * File Name: shmcreate.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-12
 * Modified: 2015-04-12
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int c, fd, flags;
    char *ptr;
    int length;

    if(argc != 3) {
        printf("Usage: shmcreate <Filename> <size>");
        return -1;
    }

    flags = O_RDWR | O_CREAT;
    while((c = getopt(argc, argv, "e")) != -1){
        switch(c){
            case 'c':
                flags |= O_EXCL;
                break;
        }
    }

    length = atoi(argv[2]);
    if((fd = shm_open(argv[1], flags, 0775)) < 0){
        printf("open memory failed\n");
        return 0;
    }

    ftruncate(fd, length);

    ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == NULL){
        printf("mmap file failed\n");
        return 0;
    }
    exit(0);
}

