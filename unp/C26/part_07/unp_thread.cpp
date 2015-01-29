/*
 * =====================================================================================
 *
 *       Filename:  unp_thread.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/23/2015 06:49:22 AM
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

#define NLOOP	5000

/* A counter, incremented by threads */
int counter;


void *doit(void*)
{
	int i, val;
	for (i = 0; i < NLOOP; i++) {
		val = counter;
		printf("%lu: %d\n", int(pthread_self()), val + 1);
		counter = val + 1;
	}
	return NULL;
}

int main()
{
	pthread_t	tidA, tidB;
	pthread_create(&tidA, NULL, &doit, NULL);	
	pthread_create(&tidB, NULL, &doit, NULL);	

	/* Wait for both threads to terminate */ 
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	exit(0);
}
