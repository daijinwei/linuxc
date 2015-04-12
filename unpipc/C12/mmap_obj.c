/**
 * Copyright (c) 2015, project
 * File Name: mmap_obj.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-12
 * Modified: 2015-04-12
 * Description: 
 **/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int max(int a, int b)
{
    return a > b? a:b;    
}

int main(int argc, char *argv[])
{
    int fd, i;
    char *ptr;
    size_t filesize, mmapsize, pagesize;
    if(argc !=4){
        printf("Usage: ./mmap_obj file filesize mmapsiz\n");
        return 0;
    }
    filesize = atoi(argv[2]);
    mmapsize = atoi(argv[3]);


    /* Open file: create ro truncte; set file size */
    if((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0775)) < 0){
        printf("Open file failed\n");
        return 0;
    }
    lseek(fd, filesize -1, SEEK_SET);
    write(fd,"", 1);
    
    ptr = mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(NULL == ptr){
        printf("mmap files failed\n");
        return 0;
    }
    close(fd);

    pagesize = sysconf(_SC_PAGESIZE);
    for(i = 0; i < max(filesize, mmapsize); i += pagesize){
        printf("ptr[%d] = %d\n", i, ptr[i]);
        ptr[i] = 1;
        printf("ptr[%d] = %d\n", i + pagesize -1, ptr[i + pagesize -1]);
        ptr[i + pagesize -1] = 1;
    }
    printf("ptr[%d] = %d\n", i, ptr[i]);
    exit(0);
}
