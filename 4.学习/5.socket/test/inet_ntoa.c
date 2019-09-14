/*************************************************************************
	> File Name:    inet_ntoa.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月16日 星期六 09时56分27秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

char *my_inet_ntoa(struct in_addr in) {
    int a[4] = {0};
    static char ip[20] = {0};
    a[0] = in.s_addr >> 24;
    a[1] = (in.s_addr >> 16) & 15;
    a[2] = (in.s_addr >> 8) & 15;
    a[3] = in.s_addr & 15;
    sprintf(ip "%d.%d.%d.%d", a[3], a[2], a[1], a[0]);
    return 0;
}

int main() {
    struct sockaddr_in;mZ    sockaddr_in;
    
}
