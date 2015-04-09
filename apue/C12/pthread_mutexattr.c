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

pthread_mutex_t *f_lock = NULL;

int count = 0;

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

    pthread_mutex_init(f_lock, &attr);

    pid_t pid;
    pid = fork();
    if(pid < 0){
        perror("fork faild");
    }else if(pid > 0){
        pthread_mutex_lock(f_lock);
        count++;
        printf("count\t%d\n", count);
        pthread_mutex_unlock(f_lock);
    }else{
        pthread_mutex_lock(f_lock);
        count++;
        printf("count\t%d\n", count);
        pthread_mutex_unlock(f_lock);
    }

}
