/*************************************************************************
	> File Name:    common.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月06日 星期六 19时27分59秒
 ************************************************************************/

#include "common.h"
int create_shm(int size) {
    int shmid = 0;
    key_t key = ftok(PATHNAME, PROJ_ID);
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
    }
    return shmid;
}

int get_shm(int size) {
    int shmid = 0;
    key_t key = ftok(PATHNAME, PROJ_ID);
    if(key < 0) perror("ftok");
    if((shmid = shmget(key, size, IPC_CREAT)) < 0) {
        perror("errget");
    }
    return shmid;
}
int destroy(int shmid) {
    shmctl(shmid, IPC_RMID, NULL);
}
