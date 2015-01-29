/*
 * =====================================================================================
 *
 *       Filename:  pthread_mutex.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/06/2015 09:14:19 PM
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
	int				f_count;	// reference count
	pthread_mutex_t	f_lock;	// a mutex
	/* many object */
};

struct foo *foo;

/*allocate the object*/
struct foo *
foo_alloc()
{
	struct foo *fp;
	fp = (struct foo *)malloc(sizeof(struct foo));
	if(fp != NULL) {
		fp->f_count =1;
		if( 0 != pthread_mutex_init(&fp->f_lock, NULL)){
			free(fp);	
			return NULL;
		}
	}
	return fp;
}

/*add a count to object*/

void 
foo_add(struct foo *fp)
{
	if(0 == pthread_mutex_lock(&fp->f_lock)) {
		fp->f_count++;	
		printf("Add:referece count %d\n",fp->f_count);
		while(1){
			if(0 == pthread_mutex_unlock(&fp->f_lock)){
				break;	
			}
		}
	}
}

/* release a referece to the object */
void 
foo_release(struct foo *fp)
{
	if(0 == pthread_mutex_lock(&fp->f_lock)) {
		if(--fp->f_count == 0) {
			printf("Des:referece count %d\n",fp->f_count);
			pthread_mutex_unlock(&fp->f_lock);	
			pthread_mutex_destroy(&fp->f_lock);
		}else{
			printf("Des:referece count %d\n",fp->f_count);
			pthread_mutex_unlock(&fp->f_lock);	
		}
	}
}

void *func1()
{
	printf("thread 1\n");
	//struct foo *foo;
	foo = foo_alloc();
	foo_add(foo);
	foo_release(foo);
}

void *func2()
{
	printf("thread 2\n");
	//struct foo *foo;
	//foo = foo_alloc();
	foo_add(foo);
	foo_add(foo);
	foo_add(foo);
	foo_add(foo);
	foo_add(foo);
	foo_add(foo);
	foo_add(foo);
	//foo_release(foo);
}

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2;
	int err;
	struct foo *fp;
	err = pthread_create(&tid1, NULL, func1, NULL);
	if (0 != err) {
		printf("can't create the thread 1 ,%s\n", strerror(err));		
	}
	err = pthread_join(tid1,&fp);

	if (0 != err) {
		printf("can't join the thread 1 ,%s\n", strerror(err));		
	}

	err = pthread_create(&tid2, NULL, func2, NULL);
	if (0 != err) {
		printf("can't create the thread 2 ,%s\n", strerror(err));		
	}

	err = pthread_join(tid1,&fp);

	if (0 != err) {
		printf("can't join the thread 1 ,%s\n", strerror(err));		
	}
	return 0;
}
