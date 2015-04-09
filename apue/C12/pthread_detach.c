/*************************************************************************
	> File Name: pthread_detache.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Apr 2015 07:20:28 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdint.h>
#include <pthread.h>

void *func(void *c){
    pthread_t tid;
    tid = pthread_self();
    printf("thread id is\t %u\n", (uint32_t)tid);
}

int make_thread(void *(*fn)(void *), void *arg)
{
    int   err;
    pthread_t   tid;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if(err != 0){
        return err;
        printf("pthread_attr_init failed\n");
    }

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err == 0){
        printf("pthread_atttr_set ok\n");
        err = pthread_create(&tid, &attr, fn, arg);
        if(err != 0){
            printf("pthread create failed\n");
        }else{
            printf("pthread create ok\n");
        }
    }
    sleep(1);

    pthread_attr_destroy(&attr);

    return err;
}

int main()
{
    int arg = 1;
    make_thread(func, &arg);
    return 0;
}
