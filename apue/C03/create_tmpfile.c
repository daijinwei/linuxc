/**
 * Copyright (c) 2015, project
 * File Name: create_tmp_file.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-12
 * Modified: 2015-05-12
 * Description: 
 **/

#include <stdio.h>

int main()
{
    char name[255];
    FILE *fp;
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);
}
