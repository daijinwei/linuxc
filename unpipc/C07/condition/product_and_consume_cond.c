/**
 * Copyright (c) 2015, project
 * File Name: product_and_consume.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-14
 * Modified: 2015-05-14
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE     1000
#define MAX_THREADS     100

struct Shared{
    pthread_mutex_t mutex;          // The pthread mutex
    int buffer[BUFFER_SIZE];        // The poll size
    int index;                      // The buffer index
    int nval;                       //The next index
} put = {
    PTHREAD_MUTEX_INITIALIZER
};

struct{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int nready;             // The number ready for consumer
} nready ={
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};

int nitems;                         // The buffer items

int min(int x, int y);
void *produce(void*);
void *consume(void*);

int min(int x, int y){
    return x < y? x : y;
}

void *produce(void *arg){
    if(0 == pthread_mutex_lock(&put.mutex)){
        if(put.index > nitems){
            if(0 != pthread_mutex_unlock(&put.mutex)){
                printf("unlock failed\n");
            }
        }
        put.buffer[put.index] = put.nval;
        put.index++;
        put.nval++;
        if(0 != pthread_mutex_unlock(&put.mutex)){
            printf("unlock failed\n");
        }

        // cond
        if(0 == pthread_mutex_lock(&nready.mutex)){
            if(nready.nready == 0){
                pthread_cond_signal(&nready.cond);
            }
            nready.nready++;
            if(0 != pthread_mutex_lock(&nready.mutex)){
                 printf("unlock failed\n");
            }
        }
        *((int *)arg) += 1;
    }else{
        printf("lock failed\n");
    }
}

void *consume(void* arg){
    int i;
    // cond
    if(0 == pthread_mutex_lock(&nready.mutex)){
        if(nready.nready == 0){
            pthread_cond_wait(&nready.cond, &nready.mutex);
        }
        nready.nready--;
        if(0 != pthread_mutex_lock(&nready.mutex)){
            printf("unlock failed\n");
        }
    }

    for(i = 0; i < nitems; ++i){
        if(put.buffer[i] != i){
            printf("buffer[%d] = %d\n", i, put.buffer[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    int nthreads;       // The thread numbers
    int i;              // xunhaunyong 
    int count[MAX_THREADS];
    pthread_t tid_produce[MAX_THREADS], tid_consume;
    if(argc != 3){
        printf("Usage: ./product_and_corume <items> <thread_nums>\n");
        exit(EXIT_FAILURE);
    }

    nthreads = min(atoi(argv[2]), MAX_THREADS);
    nitems = min(atoi(argv[1]), BUFFER_SIZE);

    if(0 != pthread_setconcurrency(nthreads)){
        printf("setconcurrency [%d] failed\n", i);
        exit(EXIT_FAILURE);
    }
    // start all produce threads
    for(i = 0; i < nthreads; ++i){
        count[i] = 0;
        if(0 != pthread_create(&tid_produce[i], NULL, produce, &count[i])){
            printf("create threads [%d] failed\n", i);
        }
    }

    for(i = 0; i < nthreads; ++i){
        if(0 != pthread_join(tid_produce[i],NULL)){
            printf("join produce threads [%d] failed\n", i);
        }
        printf("count[%d] = %d\n", i, count[i]);
    }

    // start cosume thread
    if(0 != pthread_create(&tid_consume, NULL, consume, NULL)){
            printf("create consume threads [%d] failed\n", i);
    }
    if(0 != pthread_join(tid_consume,NULL)){
        printf("join consume threads [%d] failed\n", i);
    }
}
