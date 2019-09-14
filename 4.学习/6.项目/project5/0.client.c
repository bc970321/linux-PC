/*************************************************************************
	> File Name:    0.client.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月04日 星期四 19时17分17秒
 ************************************************************************/
#include <stdio.h>
#include "./common/common.h"
#include <sys/epoll.h>

#define Port 7731
#define MAX_EVENTS 1024


int main() {
    int fd;
    fd = socket_connect(7731, "192.168.1.40");
    char buff[1024];
    while(scanf("%s", buff)) {
        send(fd, buff, strlen(buff), 0);
        memset(buff, 0, strlen(buff));
        recv(fd, buff, sizeof(buff), 0);
        printf("%s\n", buff);
        memset(buff, 0, sizeof(buff));
    }

    return 0;
}
