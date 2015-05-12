/*************************************************************************
	> File Name: my_getenv2.c
	> Author: 
	> Mail: 
	> Created Time: Thu 30 Apr 2015 09:35:01 AM CST
 ************************************************************************/

#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int i;
    for(i = 0; envp[i] != NULL; ++i){
        printf("env[%d]\t%s\n", i, envp[i]);
    }
    return 0;
}
