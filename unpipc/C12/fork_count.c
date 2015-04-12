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
#define PATH_MAX 1024

int count = 0;

char *px_ipc_name(const char *name)
{
    char    *dir, *dst, *slash;  
    //分配的空间在哪里释放的哦！@deprecated   
    if ( (dst = malloc(PATH_MAX)) == NULL )  
        return(NULL);  
    
    /* 4can override default directory with environment variable */  
    if ( (dir = getenv("PX_IPC_NAME")) == NULL ) {  
#ifdef  POSIX_IPC_PREFIX  
    dir = POSIX_IPC_PREFIX;         /* from "config.h" */  
#else  
    //dir = "/tmp";                   /* default */  
    dir = "tmp";                   /* default */  
#endif  
    }  
    slash = (dir[strlen(dir) - 1] == '/') ? "" : "/";  
    snprintf(dst, PATH_MAX, "%s%s%s", dir, slash, name);  
    return (dst);   
}


int main(int argc, char *argv[])
{
    int i, nloop;
    sem_t *mutex;
    if(2 != argc){
        printf("Usage: ./fork_count name\n");
        exit(1);
    }

    nloop = atoi(argv[1]);
    /* create, init , and unlink semaphore */
    //mutex = sem_open(px_ipc_name(SEM_NAME), O_CREAT | O_RDWR, 00777);     // not need
    mutex = sem_open(SEM_NAME, O_CREAT | O_EXCL,  FILE_MODE, 1);
    if(SEM_FAILED == mutex){
       printf("open sem failed\n");
      return -1;
    }

    if(-1 == sem_unlink(SEM_NAME)){
    //if(-1 == sem_unlink(px_ipc_name(SEM_NAME))){      // NOt need
       printf("unlink\n");
      return -1;
     }

    setbuf(stdout, NULL);       // stdout is unbuffered
    if(fork() == 0){            // child
        for(i = 0; i < nloop; ++i){
            sem_wait(mutex);
            printf("child: %d\t\n", count++);
            sem_post(mutex);
        } 
    }else{
        for(i = 0; i < nloop; ++i){
            sem_wait(mutex);
            printf("parent: %d\t\n", count++);
            sem_post(mutex);
        } 
    }
    exit(0);
}
