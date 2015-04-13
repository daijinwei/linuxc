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
#include <semaphore.h>


struct shared{
    int count;      // count ref
} shared;

sem_t *mutex;

int main(int argc, char *argv[])
{
    int fd, nloop;
    int i;
    pid_t pid;
    struct shared *ptr;

    if(argc != 4){
        printf("Usage: she_count_client <shm_filename> <sem_filename> <count>\n" );
        return -1;
    }
    nloop = atoi(argv[3]);
    /* Open a memory object*/
    if((fd = shm_open(argv[1], O_RDWR, 0775)) < 0){
        printf("open memory failed\n");
        return 0;
    }

    ptr = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    pid = getpid();
    mutex = sem_open(argv[2],0);
    if(mutex == NULL){
        printf("open sem faild\n");
        return -1;
    }
    for(i = 0; i < nloop; ++i){
        sem_wait(mutex);
        printf("pid %ld: %d\n", (long)pid, ptr->count++);
        sem_post(mutex);
        
    }
    exit(0);
}
