/*************************************************************************
	> File Name: my_lseek.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Apr 2015 04:44:57 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include <unistd.h>

int main()
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1){
        printf("can not seek\n");
    }else{
        printf("seek OK\n");
    }
    return 0;
}
