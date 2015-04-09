/*************************************************************************
	> File Name: pthread_mutexattr.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Apr 2015 07:59:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

pthread_mutex_t *f_lock = NULL;

struct shared_context{
    int ref_cnt;      // counter
    int last_process;
};

struct shared_context * sctx = NULL;
//= (struct shared_context*)shmat(shmid, 0, 0);

#define key_shared_context 1234


int main()
{
    int ret;
    f_lock = (pthread_mutex_t *)mmap(NULL, sizeof(pthread_mutex_t),
                PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);

    if(f_lock == MAP_FAILED){
        perror("mmap failed");
        exit(1);
    }

    pthread_mutexattr_t attr;
    ret = pthread_mutexattr_init(&attr);
    if(0 != ret){
        printf("init mutexattr failed\n");
        exit(1);
    }
    ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    if(0 != ret){
        printf("init mutexattr  shared failed\n");
        exit(1);
    }

    ret = pthread_mutex_init(f_lock, &attr);
    if(0 != ret){
        printf("init mutexattr  shared failed\n");
        exit(1);
    }

    key_t shmid = shmget(key_shared_context, sizeof(struct shared_context), IPC_CREAT | 0660);
    struct shared_context *stex = (struct shared_context*)shmat(shmid, 0, 0);

    pid_t pid = fork();
    if(pid <  0){
        perror("fork faild");
    }else if(pid > 0){
        printf("parent\n");
        pthread_mutex_lock(f_lock);
        sctx->ref_cnt++;
        sctx->last_process = getpid();
        shmdt((char*)sctx);
        pthread_mutex_unlock(f_lock);
    }else{
        printf("chiled\n");
        pthread_mutex_lock(f_lock);
        //struct shared_context * 
        sctx = (struct shared_context*)shmat(shmid, 0, 0);
        sctx->ref_cnt++;
        sctx->last_process = getpid();
        shmdt((char*)sctx);
        pthread_mutex_unlock(f_lock);
    }
    struct shmid_ds buf[1234];
    shmctl(shmid, IPC_RMID, buf);
    return 0;

}
