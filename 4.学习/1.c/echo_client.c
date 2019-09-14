/*************************************************************************
	> File Name:    echo_client.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月06日 星期六 20时00分46秒
 ************************************************************************/

#include "common.h"
int main() {
    int shmid = 0;
    shmid = get_shm(2048);
    void *addr = shmid(shmid, NULL, 0);

    while(1) {
        usleep(20000);
        printf("%s", addr);
    }
    
    shmdt(addr);
    destroy(shmid);
    return 0;
}

