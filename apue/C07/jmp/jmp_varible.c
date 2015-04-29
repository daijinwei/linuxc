/**
 * Copyright (c) 2015, project
 * File Name: jmp_varible.c
 * Author: David<daijinwei41@gmail.com>
 * Created: 2015-04-29
 * Modified: 2015-04-29
 * Description: 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

jmp_buf jmpbuffer;
static int globval;

int main()
{
    int             autoval;
    register int    regival;
    volatile int    volaval;
    static int      statval;

    globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;

    if(setjmp(jmpbuffer) != 0){
        printf("After longjmp:\n");
        printf("global = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
              globval, autoval, regival, volaval, statval);
        exit(0);
    }


    globval = 95; autoval = 96; regival = 97; volaval = 98; statval = 99;
    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void 
f1(int i, int j, int k, int l){
    printf("global = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n",
        globval, i, j, k, l);


    f2();
}

static void 
f2(void)
{
    longjmp(jmpbuffer, 1);
}
