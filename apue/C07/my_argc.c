/*************************************************************************
	> File Name: my_argc.c
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Apr 2015 05:26:05 PM CST
 ************************************************************************/

#include<stdio.h>

int main(int argc, char *argv[])
{
    int i;
    for(i = 0; i < argc; ++i){
        printf("argv[%d]:%s\n", i,argv[i]);
    }

    for(i = 0; argv[i] != NULL; ++i){
        printf("argv[%d]:%s\n", i,argv[i]);
    }
    return 0;
}
