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
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define BUFFER_SIZE     10
#define MAX_THREADS     100

#define SEM     "sem"
#define NEMPTY  "nempty"
#define NSTORED "nstored"

#define FILE_MODE 0755

int nitems;                         // The buffer items

int min(int x, int y);
void *produce(void*);
void *consume(void*);

int min(int x, int y){
    return x < y? x : y;
}

struct{
    int buffer[BUFFER_SIZE];
    sem_t *mutex, *nempty, *nstored;
}shared;

void *produce(void *arg){
    int i;
    for(i = 0; i < nitems; ++i){
        if(0 != sem_wait(shared.nempty)){   // Wait at leat 1 items
            printf("sem empty wait failed\n");
            return NULL;
        }

        if(0 != sem_wait(shared.mutex)){
            printf("sem mutex wait  mutex failed\n");
            return NULL;
        }
        shared.buffer[i % BUFFER_SIZE] = i;

        if(0 != sem_post(shared.mutex)){
            printf("sem mutex wait failed\n");
            return NULL;
        }

        if(0 != sem_post(shared.nstored)){ // Add 1 items to nstored
            printf("sem nstored wait mutex failed\n");
            return NULL;
        }
    }
    return NULL;
}

void *consume(void* arg){

    int i;
    for(i = 0; i < nitems; ++i){
        if(0 != sem_wait(shared.nstored)){
            printf("sem nstored  wait failed\n");
            return NULL;
        }

        if(0 != sem_wait(shared.mutex)){
            printf("sem wait mutex failed\n");
            return NULL;
        }

        if(shared.buffer[i] != i){
            printf("buffer[%d] = %d\n", i, shared.buffer[i]);
        }

        if(0 != sem_post(shared.mutex)){
            printf("sem wait mutes failed\n");
            return NULL;
        }

        if(0 != sem_post(shared.nempty)){
            printf("sem wait empty failed\n");
            return NULL;
        }
    }
    return NULL;
} 

int main(int argc, char *argv[])
{
    int nthreads;       // The thread numbers
    int i;              // xunhaunyong 
    int count[MAX_THREADS];
    pthread_t tid_produce, tid_consume;
    int flags;
    flags =  O_CREAT | O_EXCL; 
    int value = 1;

    if(argc != 2){
        printf("Usage: ./product_and_corume <items>\n");
        exit(EXIT_FAILURE);
    }

    nitems = min(atoi(argv[1]), BUFFER_SIZE);

    if(SEM_FAILED == (shared.mutex = sem_open(SEM, O_CREAT | O_EXCL, FILE_MODE, value))){
        printf("sem open sem failed\n");
    }

    if(SEM_FAILED == (shared.nempty = sem_open(NEMPTY, O_CREAT | O_EXCL, FILE_MODE, BUFFER_SIZE))){
        printf("sem open nemtpy failed\n");
    }

    if(SEM_FAILED == (shared.nstored = sem_open(NSTORED, O_CREAT | O_EXCL, FILE_MODE, 0))){
        printf("sem open nstored failed\n");
    }

    if(0 != pthread_setconcurrency(2)){
        printf("setconcurrency [%d] failed\n", i);
        exit(EXIT_FAILURE);
    }
    // start all produce threads
    if(0 != pthread_create(&tid_produce, NULL, produce, &count[i])){
        printf("create threads [%d] failed\n", i);
    }
    // start cosume thread
    if(0 != pthread_create(&tid_consume, NULL, consume, NULL)){
            printf("create consume threads failed\n");
    }

    if(0 != pthread_join(tid_produce, NULL)){
        printf("join produce threads [%d] failed\n", i);
    }

    if(0 != pthread_join(tid_consume,NULL)){
        printf("join consume threads failed\n");
    }
    if(0 != sem_unlink(SEM)){
        printf("unlink sem failed\n");
    } 

    if(0 != sem_unlink(NEMPTY)){
        printf("unlink nempty failed\n");
    } 

    if(0 != sem_unlink(NSTORED)){
        printf("unlink nstored failed\n");
    } 
    exit(0);
}
