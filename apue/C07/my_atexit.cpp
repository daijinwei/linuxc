/*************************************************************************
	> File Name: my_atexit.c
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Apr 2015 05:17:27 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Log{
public:
    Log(){std::cout << "Log::Log()" << std::endl;}
    ~Log(){std::cout << "~Log::Log()" << std::endl;}
};

Log log;

void clear(void)
{
    log;
    std::cout << "exit handler" << std::endl;
}

int main(){
    atexit(clear);
    return 0;
}
