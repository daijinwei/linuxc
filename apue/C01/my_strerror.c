/*************************************************************************
	> File Name: my_strerror.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 May 2015 11:32:24 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    exit(0);
}
