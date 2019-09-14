/*************************************************************************
	> File Name: common.h
	> Author: zhengdongqi
	> Mail: 
	> Created Time: 六  2/23 11:12:28 2019
 ************************************************************************/

#ifndef _COMMON_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>
#include <math.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <sys/shm.h>

#define max_size 1024
#define BACKLOG 30
#define _COMMON_H
#endif

#ifdef _DEBUG
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif
