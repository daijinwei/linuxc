/*************************************************************************
	> File Name: my_getenv.c
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Apr 2015 06:22:05 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main()
{
    char *p = NULL;
    p = getenv("HOME");
    printf("%s\n",p);
    return 0;
}
