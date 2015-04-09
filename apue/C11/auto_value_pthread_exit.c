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

struct foo{
	int a,b,c,d;
};

struct foo foo = {1,2,3,4};

void printf_foo(const char *s, const struct foo *fp)
{
	printf(s);
	printf("\tstructure at 0x%x\n", (unsigned)fp);
	printf("\tfoo.a = %d\n", fp->a);
	printf("\tfoo.b = %d\n", fp->b);
	printf("\tfoo.c = %d\n", fp->c);
	printf("\tfoo.d = %d\n", fp->d);
}

void *thread_func1()
{
//	struct foo foo = {1,2,3,4};
	printf_foo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *thread_func2()
{
	printf("thread 2: ID is %d\n", pthread_self());
	pthread_exit((void *)0);
}

int main()
{
	pthread_t 	tid1, tid2;
	int err;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, thread_func1, NULL);
	if(0 != err) {
		printf("Can't create thread 1, %s\n", strerror(err));
	}
	err = pthread_join(tid1, (void *)&fp);
	if(0 != err) {
		printf("Can't join 1, %s\n", strerror(err));
	}
	sleep(1);

	err = pthread_create(&tid2, NULL, thread_func2, NULL);
	if(0 != err) {
		printf("Can't create thread 2, %s\n", strerror(err));
	}
	printf_foo("parent:\n", fp);
}

