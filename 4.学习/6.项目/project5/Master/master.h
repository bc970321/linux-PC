/*************************************************************************
	> File Name:    master.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月31日 星期日 14时51分41秒
 ************************************************************************/

#ifndef _MASTER_H
#define _MASTER_H

#include "../common/common.c"

typedef struct LinkNode {
    char *IP;
    int sockFd;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList {
    LinkNode head;
    int length;
} LinkList;

LinkList *linkInit();

LinkNode *linkGetNewNode(char *, int /* Port */);

void linkInsert(LinkList *, char *, int /* Port */);

void linkErase(LinkList *, LinkNode *);

int linkSearch(LinkList *, /* const char * */ int);

void linkClear(LinkList *)

pthread_t CreateConnect(LinkList **, int);

void *dataTransmission(void *);

void *getWarningInfo()

#endif
