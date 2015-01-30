/*
 * =====================================================================================
 *
 *       Filename:  print_pid_threadid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2015 07:57:20 PM
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
#include <errno.h>

pthread_t ntid;

void printids(const char *str)
{
	pid_t		pid;
	pthread_t 	tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s\tpid: %u\ttid: %u\t(0x%x)\n",
		str, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid );
}

void* thread_func()
{
	printids("new thread: ");
	return (void *)0;
}

int main()
{
	int err;
	err = pthread_create(&ntid, NULL, thread_func, NULL);
	if( 0 != err) {
		printf("Can not create the thread: %s\n", strerror(err));	
	}

	printids("main thread: ");
	sleep(1);
	exit(0);
}
