/**
 * Copyright (c) 2015, project
 * File Name: sem_getvalue.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-18
 * Modified: 2015-05-18
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main(int argc, char *argv[])
{
    sem_t *sem;
    int val;

    if(argc != 2){
        printf("Usage: sem_wait <name>\n");
    }

    if(SEM_FAILED == (sem = sem_open(argv[1], 0))){
        printf("sem open failed");
    }

    if(-1 == sem_wait(sem)){
        printf("sem wait failed\n");
    }
    if(-1 == (sem_getvalue(sem, &val))){
        printf("sem getvalue failed\n");
    }
    printf("value = %d\n", val);
    exit(0);
}
