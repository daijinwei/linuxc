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

#define SHM_FILE "shm_r"

int main(int argc, char *argv[])
{
    int c, fd, flags;
    char *ptr;
    int i;
    struct stat stat;
    //int length = 100;

    if((fd = shm_open(argv[1], O_RDWR | O_CREAT, 0775)) < 0){
        printf("open memory failed\n");
        return 0;
    }

    fstat(fd, &stat);
    ptr = mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if(ptr == NULL){
        printf("mmap file failed\n");
        return 0;
    }
    for(i = 0; i < stat.st_size; i++){
       *ptr++ = i % 256; 
    }
    exit(0);
}

