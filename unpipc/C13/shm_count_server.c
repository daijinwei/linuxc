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
    int c, fd, flags;
    int i;
    struct shared *ptr;

    shm_unlink(argv[1]);    // Check if this failed
    /* Open a memory object*/
    if((fd = shm_open(argv[1], O_RDWR | O_CREAT, 0775)) < 0){
        printf("open memory failed\n");
        return 0;
    }

    ftruncate(fd, sizeof(struct shared));
    ptr = mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    sem_unlink(argv[2]);    // Check if this failed 
    mutex = sem_open(argv[2], O_CREAT | O_EXCL, 0775, 1);
    sem_close(mutex);
    exit(0);
}
