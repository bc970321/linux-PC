/*************************************************************************
	> File Name: Client.c
	> Author: 
	> Mail: 
	> Created Time: 四  2/21 17:56:23 2019
        Time      Path            Time
    0   Proci     ProcLog.sh      30
    1   Cpu       CpuLog.sh       5
    2   Sys       SysInfo.sh      60
    3   User      User.sh         60
    4   Mem       MemLog.sh       5
    5   Disk      DiskLog.sh      60
 ************************************************************************/
#include "./common/common.h"
#include

int main(int argc, char *argv[]) {
    int port, server_listen;

    if(argc != 2) {
        printf("Usage: ./test pirt!\n");
        exit(1);
    }
    
    port = atoi(argv[1]);

    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket:");
        return -1;
    }
    
    if (bind(server_listen, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind:");
        close(server_listen);
        return -1;
    }

    if (listen(server_listen, 20) < 0) {
        perror("listen:");
        close(server_listen);
        return -1;
    }

    while(1) {
        struct sockaddr_in client_addr;
        char name[20] = {0};
        char buff[255] = {0};
        int pid = 0;
        int len = sizeof(client_addr);
        if ((sock_fd = accept(server_listen, (struct sockaddr *)&client_addr, &len) < 0) {
            perror("accept:");
            continue;
        }
        if ((pid = fork()) < 0) {
            printf("Error in fork!\n");
            continue;
        }
        if (pid == 0) {
            close(server_listen);
            recv(sock_fd, name, 20, 0);
            printf("%s 上线!\n", name);
            while( recv(sock_fd, buff, strlen(buff), 0) > 0) {
                printf("%s: %s\n", name, buff);
                fflush(stdout);
                memset(buff, 0, sizeof(buff));
            }
            printf("%s 下线\n", name);
            close(sock_fd);
            exit(0);
        }
        close(sock_fd);
    }

    return 0;
}


