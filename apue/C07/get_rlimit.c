/**
 * Copyright (c) 2015, project
 * File Name: get_rlimit.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-29
 * Modified: 2015-04-29
 * Description: 
 **/

#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit limit;
    if(0 == getrlimit(RLIMIT_CORE,&limit)){
        printf("limit_cur \t%ld\n", limit.rlim_cur);
        printf("limit_max \t%ld\n", limit.rlim_max);
    }else{
        printf("return failed\n");
    }
}
