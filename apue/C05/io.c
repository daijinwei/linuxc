/*************************************************************************
	> File Name: io.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 May 2015 03:36:56 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    while((n = getc(stdin))){
        if(putc(n, stdout) == EOF){
            printf("putc error\n");
        }
    }

    if(ferror(stdin)){
        printf("stdinerror\n");
    }
    exit(0);
}
