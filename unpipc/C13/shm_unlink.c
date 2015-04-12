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
    if(argc != 2){
        printf("Usage: ./shm_unlink <filename>\n");
        return -1;
    }
    shm_unlink(argv[1]);
    exit(0);
}
