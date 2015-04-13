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

int main(int argc, char *argv[])
{
    int i, nloop;
    int fd;
    char buf[1024];
    int *addr = NULL;
    sem_t *mutex;
    if(3 != argc){
        printf("Usage: ./fork_count_map name count\n");
        exit(1);
    }

    // loop count
    nloop = atoi(argv[2]);

    /* open file , initilize to 0, map into mameroy, argv[1], mmap file */
    fd = open("/dev/zero", O_RDWR | O_CREAT , 0775);
    if(fd < 0){
        return -1;
    }

    addr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    /* create, init , and unlink semaphore */
    mutex = sem_open(SEM_NAME, O_CREAT | O_EXCL,  FILE_MODE, 1);
    if(SEM_FAILED == mutex){
       printf("open sem failed\n");
      return -1;
    }

    if(-1 == sem_unlink(SEM_NAME)){
       printf("unlink\n");
      return -1;
     }

    setbuf(stdout, NULL);       // stdout is unbuffered
    if(fork() == 0){            // child
        for(i = 0; i < nloop; ++i){
            sem_wait(mutex);
            printf("child: %d\t\n", (*addr)++);
            sem_post(mutex);
        } 
        exit(0);
    }else{
        for(i = 0; i < nloop; ++i){
            sem_wait(mutex);
            printf("parent: %d\t\n", (*addr)++);
            sem_post(mutex);
        } 
        exit(0);
    }
    return 0;
}
