/*************************************************************************
	> File Name: pthread_rwlock.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Apr 2015 05:13:26 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Job Job;
struct Job{
    Job   *j_prev;
    Job   *j_next;
    pthread_t j_id;   // Which pthead has this job
};

