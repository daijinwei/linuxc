/*************************************************************************
	> File Name: pthread_conditon.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Apr 2015 05:23:38 PM CST
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>

struct Msg{
    struct Msg *next;
    int data;
};

struct Msg *workq;


pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;


void process_msg(void)
{
    struct Msg *mp;
    for( ; ;){
        pthread_mutex_lock(&qlock);
        while(workq != NULL){
            pthread_cond_wait(&qready,&qlock);
        }

        mp = workq;
        workq = mp->next;
        pthread_mutex_unlock(&qlock);
    }
}

void enqueue_msg(struct Msg *mp){
    pthread_mutex_lock(&qlock);
    mp->data = 2;
    mp->next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}


int main()
{
    struct Msg msg;
    msg.data = 1;

    enqueue_msg(&msg);
    process_msg();
    return 0;
}
