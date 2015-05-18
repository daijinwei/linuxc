/**
 * Copyright (c) 2015, project
 * File Name: sem_unlink.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-18
 * Modified: 2015-05-18
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: sem_unlink <name>");
    }

    if(-1 == sem_unlink(argv[1])){
        printf("sem_unlink sem failed\n");
    }
    exit(0);
}
