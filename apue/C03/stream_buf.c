/**
 * Copyright (c) 2015, project
 * File Name: stream_buf.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-05-12
 * Modified: 2015-05-12
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>

void pr_stdio(const char *name, FILE *fp);
void pr_stdio(const char *name, FILE *fp){
    if(fp == NULL) exit(0);
    printf("stream = %s ",name);

    if(fp->_IO_file_flags & _IO_UNBUFFERED){
        printf("undefined");
    }else if(fp->_IO_file_flags & _IO_LINE_BUF){
        printf("line buffer");
    }else{
        printf("full buffer");
    }

    printf(" , bufsize = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

int main()
{
    FILE *fp = NULL;
    printf("enter any charactors\n");
    if(getchar() == EOF){
        printf("getchar error\n");
        exit(-1);
    }

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if((fp = fopen("/etc/motd", "r")) == NULL){
        printf("fopen error\n");
        exit(-1);
    }
    printf("fp addr0 = %p\n", fp);
    if(getc(fp) == EOF){
        printf("fopen error\n");
    }
    printf("fp addr1 = %p\n", fp);

    exit(0);
}
