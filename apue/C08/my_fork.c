/**
 * Copyright (c) 2015, project
 * File Name: my_fork.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-28
 * Modified: 2015-04-28
 * Description: 
 **/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int i = 0;
    for(i; i < 2; ++i){
        fork();
    }

    printf("hello world\n");
}
