/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Apr 2015 06:23:22 PM CST
 ************************************************************************/

#include<stdio.h>

char *test()
{
    char p[] = "hello world";
    return p;
}

int main()
{
    char *p = NULL;
    p = test();
    printf("%s\n", p);
    return 0;
}
