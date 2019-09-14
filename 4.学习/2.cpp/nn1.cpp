/*************************************************************************
	> File Name:    nn1.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月29日 星期一 15时15分33秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <pthread.h>

struct sm_msg {
    char buff[1024];
    pthread_mutex_t sm_mutex;
    pthread_cont_t sm_ready;
};

int main() {
    int shmid, pid;
    
    char *share_memory = NULL;
    
    pthread_mutexattr_t m_attr;
    pthread_condattr c_attr;

    pthread_mutexattr_init(&m_attr);
    pthread_condattr_init(&c_attr);

    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);

    if ((shmid = shmget(IPC_PRIVATE, 4096, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if (((share_memory = shmat(shmid, 0, 0)) < 0) {
        perror("shmat");
        exit(1);
    }
    
    struct sm_msg *msg = (struct sm_msg*)share_memory;


    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        while (1) {
            //printf("In Child:\n");
            scanf("%s", share_memory);
            kill(getppid(), 10);
        }
    } else {
        while(1) {
            signal(10, print);
            pause;
        } 
    }
    
    return 0;
}
