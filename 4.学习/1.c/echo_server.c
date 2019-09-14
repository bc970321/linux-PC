/*************************************************************************
	> File Name:    echo_server.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月06日 星期六 20时05分56秒
 ************************************************************************/

#include "common.h"
int main() {
    int shmid = 0;
    shmid = create_shm(2048);
    void *addr = shmat(shmid, NULL, 0);

    while(1) {
        scanf("%[^\n]s", addr);
        getchar();
        strcat(addr,"\n");
        fflush(stdin);
        usleep(2000);
        memset(addr, 0, sizeof(addr));
    }
    shmdt(addr);
    destory(shmid);
    return 0;
}

