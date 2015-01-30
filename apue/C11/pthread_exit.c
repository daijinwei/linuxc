 /**
 *=====================================================================================
 *
 *       Filename:  pthread_exit.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2015 08:19:23 PM
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
#include <pthread.h>
#include <string.h>

void* thread_func1()
{
	printf("thread 1 returning\n");
	return ((void *)1);
}

void* thread_func2()
{

	printf("thread 2 exiting\n");
	pthread_exit((void*)2);
}

int main()
{
	int err;
	pthread_t	tid1, tid2;

	void *exit_status;

	err = pthread_create(&tid1, NULL, thread_func1, NULL);
	if(0 != err){
		printf("Can't create thread 1: %s\n", strerror(err));
	}

	err = pthread_create(&tid2, NULL, thread_func2, NULL);
	if(0 != err){
		printf("Can't create thread 1: %s\n", strerror(err));
	}

	err = pthread_join(tid1,&exit_status);
	if(0 != err) {
		printf("Can't join the thread 1 : %s\n", strerror(err));	
	}


	printf("thread 1 exit code %d\n", (int)exit_status);
	err = pthread_join(tid2,&exit_status);
	if(0 != err) {
		printf("Can't join the thread 2 : %s\n", strerror(err));	
	}
	printf("thread 2 exit code %d\n", (int)exit_status);
	exit(0);
}
