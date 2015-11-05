#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

/* Version without signal handing */
int system_nosignal(const char *cmdstring);

#endif /// _SYSTEM_H_
