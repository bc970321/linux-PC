/*************************************************************************
	> File Name:    common.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月31日 星期日 14时27分00秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

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

#define MAXBUFF 4096

#define CPU_INFO 100
#define DISK_INFO 101
#define MALIPS_INFO 102
#define MEM_INFO 103
#define SYS_INFO 104
#define USER_INFO 105
#define DATANULL 106
#define CLOSE_NOW 107

#define CPU_WARN 200
#define DISK_WARN 201
#define MALIPS_WARN 202
#define MEM_WARN 203
#define SYS_WARN 204
#define USER_WARN 205

/* 配置文件路径 */

#define CONF_CLIENT "/home/bicheng/project5/Client/client.conf"
#define CONF_MASTER "/home/bicheng/project5/Master/master.conf"

/* 程序运行日志路径 */
//#define RUN_LOG_SERVER "/var/log/SHMS-server/SHMS-Server.log"
//#define RUN_LOG_MASTER "/var/log/SHMS-master/SHMS-Master.log"

/* 每次最大发送长度 */
#define TRANS_MAX 1024

#ifdef _DEBUG
#define DBG(fmt, args...) printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

char *getConf(const char * /* the name of need varialbe */ , const char * /* path and file name. */);

int sockServer(char * /* IP */ , int /* Port */ );

int sockClient(char * /* IP */ ,int /* Port */);

int sockGetFromIP(char * /* save IP */, struct sockaddr_in *);

int sendClose(int);

int StrtoInt(char * /* Target string */);

int writePiLog(const char *, char *);

#endif
