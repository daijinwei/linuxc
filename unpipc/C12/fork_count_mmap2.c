/**
 * Copyright (c) 2015, project
 * File Name: fork_count.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-12
 * Modified: 2015-04-12
 * Description: 
 **/

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <unistd.h>   
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
#include <semaphore.h> 

#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SEM_NAME "mysem"

struct Shared{
    sem_t   mutex;      /* The mutex: a Posix memory-based semaphore */ 
    int     count;      /* and the counter */
} shared;

int main(int argc, char *argv[])
{
    int i, nloop;
    int fd;
    char buf[1024];
    struct Shared *addr = NULL;
    sem_t *mutex;

    if(3 != argc){
        printf("Usage: ./fork_count_map name count\n");
        exit(1);
    }

    // loop count
    nloop = atoi(argv[2]);

    /* open file , initilize to 0, map into mameroy, argv[1], mmap file */
    fd = open(argv[1], O_RDWR | O_CREAT , 0775);
    if(fd < 0){
        return -1;
    }

    if(write(fd, &shared, sizeof(struct Shared)) < 0){
        return -1;
    }
    addr = mmap(NULL, sizeof(buf), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    /* init , and unlink semaphore */
    sem_init(&addr->mutex, 1, 1);

    setbuf(stdout, NULL);       // stdout is unbuffered
    if(fork() == 0){            // child
        for(i = 0; i < nloop; ++i){
            sem_wait(&(addr->mutex));
            printf("child: %d\t\n", addr->count++);
            sem_post(&(addr->mutex));
        } 
        exit(0);
    }else{
        for(i = 0; i < nloop; ++i){
            sem_wait(&(addr->mutex));
            printf("parent: %d\t\n", addr->count++);
            sem_post(&(addr->mutex));
        } 
        exit(0);
    }
    return 0;
}
