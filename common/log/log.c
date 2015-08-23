#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include "log.h"

static  const char *levels[] = {"NONE","FATAL","ERROR","WARNING","INFO","DEBUG","TRACE"};

void get_now_time(char *buf_time){
    struct tm result;
    struct tm *local = NULL;
    time_t now_time = time(NULL);

    if (NULL == buf_time) return;

    local = localtime_r(&now_time, &result);
    if(NULL != local) {
        strftime(buf_time,BUF_TIME_SIZE,"%Y-%m-%d %H:%M:%S", &result);
    }
}

void write_to_log(int level, const char *file, int line, const char *message, ...){
    int ret;
    char buf[BUF_SIZE]; 
    char buf_time[BUF_TIME_SIZE];

    memset(buf, BUF_SIZE, 0);

    va_list arg_ptr;
    va_start(arg_ptr, message); 
    vsnprintf(buf, BUF_SIZE, message, arg_ptr);
    va_end(arg_ptr);

    memset(buf_time, BUF_SIZE, 0);
    get_now_time(buf_time);

    if (-1 != ret) {
        fprintf(stdout, "[%s][%s][file: %s | line: %d | pid: %u] %s", levels[level], buf_time, file, line, getpid(),buf);
    }
}
