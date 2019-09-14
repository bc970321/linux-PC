/*************************************************************************
	> File Name:    common.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月31日 星期日 14时33分42秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"

/*服务器使用*/
int socket_create(int port) {
    int _socket_fd;
    struct sockaddr_in _server_addr;
    //创建套接字
    if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(-1);
    }
    //准备网络通信地址
    memset(&_server_addr, 0, sizeof(_server_addr));//数据初始化清零
    _server_addr.sin_family = AF_INET;//设置为TCP通讯
    _server_addr.sin_port = htons(port);//端口
    _server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址
    //绑定连接
    if (bind(_socket_fd, (struct sockaddr*)&_server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind");
        exit(-1);
    }
    //设置监听
    if (listen(_socket_fd, 20) < 0) {
        perror("listen");
        close(_socket_fd);
        exit(-1);
    }
    return _socket_fd;
}

/*客户使用*/
int socket_connect(int port, char *host) {
    int _socket_fd;
    struct sockaddr_in _client_addr;
    //创建套接字
    if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        close(_socket_fd);
        return -1;
    }
    //设置服务器
    memset(&_client_addr, 0, sizeof(_client_addr));//数据初始化清零
    _client_addr.sin_family = AF_INET;//设置为TCP通讯
    _client_addr.sin_port = htons(port);//端口
    _client_addr.sin_addr.s_addr = inet_addr(host);//IP地址
    //链接服务器
    if (connect(_socket_fd, (struct sockaddr *)&_client_addr, sizeof(_client_addr)) < 0) {
        perror("connect");
        close(_socket_fd);
        return 1;
    }
    return _socket_fd;
}
//获取配置文件
int get_conf_value(char *pathname, char* key_name, char *value) {
    FILE *fd = NULL;
    char *line = NULL;
    char *substr = NULL;
    ssize_t read = 0;//有符号整形 类型定义 字节
    size_t len = 0;//无符号整形 类型定义 字节
    int tmp = 0;

    fd = fopen(pathname, "r");
    
    if (fd == NULL) {
        printf("Error in Open\n");
        exit(1);
    }
    
    while ((read = getline(&line, &len, fd)) != -1) {//读取一行 到/0 返回读取字节数
        DBG("%s", line);
        fflush(stdout);
        substr = strstr(line, key_name);//在字符串1中 查找字符串2的首次位置 返回地址
        if (substr == NULL) {
            continue;
        } else {
            tmp = strlen(key_name);
            if (line[tmp] == '=') {
                DBG("tmp = %d\n", tmp);
                DBG("read = %d\n", read);

                strncpy(value, &line[tmp + 1], (int)read - tmp - 1);
                tmp = strlen(value);
                *(value + tmp - 1) = '\0';
                break;
            }
            else {
                printf("Next\n");
                continue;
            }
        }
    }
    return 0;
}

bool check_connect(struct sockaddr_in addr, long timeout) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DBG("%s\n", strerror(error));
        return -1;
    }
    int error = -1, len;
    len = sizeof(int);
    struct timeval tm;
    fd_set set;
    unsigned long ul = 1;
    ioctl(sockfd, FIONBIN, &ul);//进程管理函数 设置为非阻塞模式
    bool ret = false;
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        tm.tv_sec = 0;
        tm.tv_usec = timeout;
        FD_ZERO(&set);//将set清零使集合中不含任何fd
        FD_SET(sockfd, &set);//将sockfd 加入set集合
        if (select(sockfd + 1, NULL, &set, NULL, &tm) > 0) {
        getsockopt(sockfd, SOL_SOCKET, sockfd, &error, (socklen_t * )&len);//获取一个套接口选项
            if (error == 0) {
                ret = true;
            } else ret = false;
        } else ret = false;
    } else {
        ret = true;
    }
    close(sockfd);
    return ret;
}

bool client_heart(char *ip, int port) {
    bool ret = true;
    int fd;
    if ((fd = socket_connect(port, ip) < 0)) {
        ret = false;
    }
    close(fd);
    return ret;
}

bool connect_nonblock(int port_master, char *ip_master, long n) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error in connect_nonblock!\n");
        exit(1);
    }

    bool ret  = false;
    return ret;
}
//返回接收到的master端发送的序号
int recv_response(int sockfd) {
    int number;
    if ((recv(sockfd, &number, sizeof(int), 0)) <= 0) {
        perror("recv response error:");
        return -1;
    }
    return number;
}

int send_response(int number, int sockfd) {
    FILE *file;
    char buff[1000] = {0};
    char filename[50];
    switch(number) {//将.log文件中的内容存到logname中
        case 100://cpu
			file = popen("cat ../script/log/cpu.log", "r");
            strcpy(filename, "../script/log/cpu.log");
            break;
        case 101://mem
            file = popen("cat ../script/log/mem.log", "r");
            strcpy(filename, "../script/log/mem.log");
            break;
        case 102://disk
            file = popen("cat ../script/log/disk.log", "r");
            strcpy(filename, "../script/log/disk.log");
            break;
        case 103://pro
            file = popen("cat ../script/log/pro.log", "r");
            strcpy(filename, "../script/log/pro.log");
            break;
        case 104://sysinfo
            file = popen("cat ../script/log/sysinfo.log", "r");
            strcpy(filename, "../script/log/sysinfo.log");
            break;
        case 105://userinfo
            file = popen("cat ../script/log/userinfo.log", "r");
            strcpy(filename, "../script/log/userinfo.log");
            break;
    }
    while(1) {
        if (fread(buff, 8, 1000 / 8, file) == 0) break;
        if (send(sockfd, buff, strlen(buff), 0) < 0) {
            perror("error in send_response!");
        }
        memset(buff, 0, sizeof(buff));
    }
    pclose(file);
    remove(filename);
    sleep(1);
    return 0;
}
