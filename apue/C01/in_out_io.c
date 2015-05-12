/*************************************************************************
	> File Name: in_out_io.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 May 2015 09:47:13 AM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    while((c = getc(stdin)) != EOF){
        if(putc(c,stdout) == EOF){
            printf("stdout error\n");
        }
    }
    if(ferror(stdin)){
       printf("stdin error\n");
    }
    exit(0);
}

