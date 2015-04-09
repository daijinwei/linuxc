/*
 * =====================================================================================
 *
 *       Filename:  auto_value_pthread_exit.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2015 08:50:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char*)arg);
}

void *thread_func1(void *arg)
{
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");
    if(arg)
        return((void*)1);

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void *)1);
}

void *thread_func2(void *arg)
{
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push complete\n");
    if(arg)
        pthread_exit((void*)2);

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);

    return ((void *)2);
}

int main()
{
	pthread_t 	tid1, tid2;
	int err;
  int tret;

	err = pthread_create(&tid1, NULL, thread_func1, (void *)1);
	if(0 != err) {
		printf("Can't create thread 1, %s\n", strerror(err));
	}

	err = pthread_create(&tid2, NULL, thread_func2, (void *)1);
	if(0 != err) {
		printf("Can't create thread 2, %s\n", strerror(err));
	}

	err = pthread_join(tid1, &tret);
	if(0 != err) {
		printf("Can't join 1, %s\n", strerror(err));
	}
  printf("thread 1 exit code %d\n", (int)tret);

	err = pthread_join(tid2, &tret);
	if(0 != err) {
		printf("Can't join 1, %s\n", strerror(err));
	}
  printf("thread 2 exit code %d\n", (int)tret);

}

