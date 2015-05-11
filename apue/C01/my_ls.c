/**
 * Copyright (c) 2015, project
 * File Name: my_ls.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-11
 * Modified: 2015-05-11
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dir = NULL;
    struct dirent *dirent = NULL;
    if(argc != 2){
        printf("Usage: my_ls <dir>\n");
        exit(0);
    }
    if((dir = opendir(argv[1])) == NULL){
        printf("open dir failed\n");
        exit(0);
    }
    while((dirent = readdir(dir)) != NULL){
        printf("%s\n", dirent->d_name);
    }
    closedir(dir);
    return 0;
}
