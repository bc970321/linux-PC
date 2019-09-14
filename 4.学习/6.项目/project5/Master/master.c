/*************************************************************************
	> File Name:    master.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月31日 星期日 14时57分28秒
 ************************************************************************/

#include "./master.h"
#include <stdbool.h>
int masterConnect() {

    /* Get threadNum from master.conf */

    char *threadNum = getConf("threadNum", CONF_MASTER);
    if (threadNum == NULL) {
        perror("master.conf error (don't have threadNum)");
        return 1;
    }
    int MaxNum = StrtoInt(threadNum);
    free(threadNum);

    LinkList *list[MaxNum];

    for (int i = 0; i < MaxNum; i++) {
        list[i] = linkInit();
    }

    /* 开启子线程，在子线程中开启socket服务，监控上线服务器，存储连接套接字。*/

    pthread_t listenThread = CreateConnect(list, MaxNum);
    if (listenThread  == -1)  {
        exit(1);
    }

    /* 紧急警报监听 */

    pthread_t warningThread;
    if (pthread_create(&warningThread, NULL, getWarningInfo, NULL)) {
        perror("masterConnect.c create thread getWarningInfo:");
        return 1;
    }

    /* 创建指定数量线程，将存储服务器信息的链表作为参数传递给dataTransmission函数 */

    pthread_t thread[MaxNum];
    for (int i = 0; i < MaxNum; i++) {
        if (pthread_create(&thread[i], NULL, dataTransmission, (void *)list[i])) {
            perror("pthread_create dataTransmission");
            return 1;
        }
    }

    for (int i = 0; i < MaxNum; i++) {
        pthread_join(thread[i], NULL);
    }
    pthread_join(listenThread, NULL);
    pthread_join(warningThread, NULL);

    pthread_exit(NULL);
    return 0;
}

LinkList *linkInit() {
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->head.next = NULL;
    p->length = 0;
    return p;
}

LinkNode *linkGetNewNode(char *IP, int sockFd) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->IP = strdup(IP);
    p->sockFd = sockFd;
    p->next = NULL;
    return p;
}

void linkInsert(LinkList *l, char *IP, int sockFd) {
    LinkNode *p = &(l->head);

    while (p->next) {
        p = p->next;
    }

    LinkNode *insert_node = linkGetNewNode(IP, sockFd);
    insert_node->next = p->next;
    p->next = insert_node;
    l->length += 1;
    return ;
}

// delete
void linkErase(LinkList *l, LinkNode *needDelete) {
    LinkNode *p = &(l->head);

    while (p->next) {
        if (p->next == needDelete) {
            break;
        }
    }

    if (p->next == NULL) {
        return ;
    }
    LinkNode *delete_node = p->next;
    p->next = p->next->next;
    free(delete_node->IP);
    close(delete_node->sockFd);
    free(delete_node);
    l->length -= 1;
    return ;
}

void linkClear(LinkList *l) {
    if (l->head.next == NULL) {
        return ;
    }
    LinkNode *now_node = l->head.next, *free_node;
    while (now_node) {
        free_node = now_node;
        now_node = now_node->next;
        close(free_node->sockFd);
        free(free_node->IP);
        free(free_node);
    }
    free(l);
    return ;
}

int search(LinkList *list, /* const char *IP */int sockFd) {
    LinkNode *currentNode = list->head.next;
    while (currentNode) {
        if (/* !strcmp(currentNode->IP, IP) */ currentNode->sockFd == sockFd) {
            return 0;
        }
        currentNode = currentNode->next;
    }
    return 1;
}

void *getWarningInfo() {
    signal(SIGPIPE, SIG_IGN);

    /* 从配置文件中获取本机IP  */

    char *localIP = getConf("localIP", CONF_MASTER);
    if (localIP == NULL) {
        perror("master.conf error (don't have localIP)");
        exit(1);
    }

    /* 从配置文件中获取本机紧急监听开启哪个端口 */

    char *strLocalWPort = getConf("localWPort", CONF_MASTER);
    if (strLocalWPort == NULL) {
        perror("master.conf error (don't have locaWPort)");
        exit(1);
    }
    int localWPort = StrtoInt(strLocalWPort);
    free(strLocalWPort);


    /* 开启紧急监听，等待服务器端连入*/

    int sockFd, sockSon;
    struct sockaddr_in addrSon;
    char IP[20] = {'\0'};
    char warning[MAXBUFF] = {'\0'};

    sockFd = sockServer(localIP, localWPort);
    socklen_t addrSonLen = sizeof(addrSon);
    free(localIP);

    while (1) {
        sockSon = accept(sockFd, (struct sockaddr *)&addrSon, &addrSonLen);
        if (sockSon < 0) {
            perror("getWarningInfo.c accept error");
            return NULL;
        }

        memset(IP, '\0', sizeof(IP));
        sockGetFromIP(IP, (struct sockaddr_in *)&addrSon);

        memset(warning, '\0', sizeof(warning));
        if (recv(sockSon, warning, MAXBUFF, 0) == -1) {
            perror("getWarningInfo.c recv");
            continue;
        }

        char *logPath = getConf("logPath", CONF_MASTER);
        if (logPath == NULL) {
            perror("master.conf error (don't have logPath)");
        }
        if (logPath[(int)strlen(logPath) - 1] == '/') {
            logPath[(int)strlen(logPath) - 1] = '\0';
        }
        char *logpath = (char *)malloc(sizeof(char) * ((int)strlen(logPath) + (int)strlen(IP) + 1 + 5 /* 多开5个防止溢出 */ ));
        strcpy(logpath, logPath);
        strcat(logpath, "/");
        strcat(logpath, IP);
        strcat(logPath, "/warning.log");

        free(logPath);

        if (writePiLog(logpath, warning) == 1) {
            perror("getWarningInfo.c (writePiLog error)");
            return NULL;
        }

    }

    return NULL;
}

int recvData(int sockFd, char *logPath) {

    for (int i = 0; i < 6; i++) {

        int dataType = 100 + i;

        if (send(sockFd, &dataType, sizeof(int), 0) < 0) {
            perror("recvData (send INFO)");
            return -1;
        }

        /* receive dataSize. */

        int dataSize = MAXBUFF;
        // int recvRet = 1;
        // recvRet = recv(sockFd, &dataSize, sizeof(int), 0);
        // if(recvRet == -1) {
        //     perror("recvData (recv dataSize)");
        //     return -1;
        // } else if (recvRet == 0) {
        //     break;
        // } else if (dataSize <= 0) {
        //     perror("dataSize error");
        //     return -1;
        // } else if (dataSize == CLOSE_NOW) {
        //     return 0;
        // }

        /* receive data. */

        char logFile[MAXBUFF] = {'\0'};
        strcpy(logFile, logPath);

        switch (dataType) {
            case 100 : {
                strcat(logFile, "/cpu.log");
            } break;
            case 101 : {
                strcat(logFile, "/disk.log");
            } break;
            case 102 : {
                strcat(logFile, "/malips.log");
            } break;
            case 103 : {
                strcat(logFile, "/mem.log");
            } break;
            case 104 : {
                strcat(logFile, "/sys.log");
            } break;
            case 105 : {
                strcat(logFile, "/user.log");
            } break;
        }

        char Data[MAXBUFF] = {'0'};

        if (recv(sockFd, Data, sizeof(char) * (dataSize), 0) < 0) {
            perror("recvData (recv data)");
            return -1;
        } else if (!strcmp(Data, "NULL")) {
            perror("recvData() (receive data is NULL)");
            continue;
        }
        printf("receive Data : <%s>\n", Data);
        /* 将数据写入日志文件 */

        if (writePiLog(logFile, Data) == 1) {
            return -1;
        }

    }

    return 0;
}

void *dataTransmission(void *arg) {
    signal(SIGPIPE, SIG_IGN);

    /* get logPath. */

    char *templogPath = getConf("logPath", CONF_MASTER);
    if (templogPath == NULL) {
        perror("master.conf error (don't have logPath)");
    }
    if (templogPath[(int)strlen(templogPath) - 1] == '/') {
        templogPath[(int)strlen(templogPath) - 1] = '\0';
    }
    char logPath[MAXBUFF] = {'\0'};
    strcpy(logPath, templogPath);
    free(templogPath);

    LinkList *list = (LinkList *)arg;

    while (list->head.next == NULL) sleep(1);
    LinkNode *currentNode = list->head.next;

    char logpath[MAXBUFF] = {'\0'};
    char Cmd[MAXBUFF] = {'\0'};
    while (1) {
        while (list->length == 0) sleep(1);

        memset(logpath, '\0', sizeof(logpath));
        strcpy(logpath, logPath);

        strcat(logpath, "/");
        strcat(logpath, currentNode->IP);

        memset(Cmd, '\0', sizeof(Cmd));
        strcpy(Cmd, "mkdir ");
        strcat(Cmd, logpath);
        strcat(Cmd, " 2> /dev/null");
        if (system(Cmd) == -1) {
            perror("recvData() (mkdir log directory)");
            break;
        }

        /* 读取套接字sockFd，进行数据传输 */

        if (recvData(currentNode->sockFd, logpath) == -1) {
            perror("recvData error");
            break;
        }

        /* 断开连接 */

        linkErase(list, currentNode);

        if (currentNode->next == NULL) {
            while (list->head.next == NULL) sleep(1);
            currentNode = list->head.next;
        } else {
            currentNode = currentNode->next;
        }
    }
    linkClear(list);
    return NULL;
}

typedef struct args {
    LinkList **list;
    int listNum;
} Args;
Args arg;

void *startListen(void *None) {

    /* 从配置文件中获取本机IP  */

    char *localIP = getConf("localIP", CONF_MASTER);
    if (localIP == NULL) {
        perror("master.conf error (don't have localIP)");
        return NULL;
    }

    /* 从配置文件中获取本机监听开启哪个端口 */

    char *strLocalPort = getConf("localPort", CONF_MASTER);
    if (strLocalPort == NULL) {
        perror("master.conf error (don't have localPort)");
        free(localIP);
        return NULL;
    }
    int localPort = StrtoInt(strLocalPort);
    free(strLocalPort);

    /* 从配置文件中获取连接上限 */

    char *strConnectMax = getConf("connectMax", CONF_MASTER);
    if (strConnectMax == NULL) {
        perror("master.conf error (don't have connectMax)");
        free(localIP);
        return NULL;
    }
    int connectMax = StrtoInt(strConnectMax);
    free(strConnectMax);

    /* 开启监听，等待服务器端连入*/

    int sockFd, sockSon;
    struct sockaddr_in addrSon;
    char IP[20] = {'\0'};

    sockFd = sockServer(localIP, localPort);
    socklen_t addrSonLen = sizeof(addrSon);
    free(localIP);

    while (1) {

        /* 读取所有链表的长度，获取最短链表(minLenList)和总共连接数(nowConnectNum)。*/

        LinkList *minLenList = arg.list[0];
        int nowConnectNum = arg.list[0]->length;
        for (int i = 1; i < arg.listNum; i++) {
            nowConnectNum += arg.list[i]->length;
            minLenList = (arg.list[i]->length < minLenList->length ? arg.list[i] : minLenList);
        }

        if (nowConnectNum >= connectMax) {
            sleep(1);
            continue;
        }

        /* 调用accept接受连入 */

        sockSon = accept(sockFd, (struct sockaddr *)&addrSon, &addrSonLen);
        if (sockSon < 0) {
            break;
        }
        memset(IP, '\0', sizeof(IP));
        sockGetFromIP(IP, (struct sockaddr_in *)&addrSon);

        /* 将新建连接插入链表 */

        linkInsert(minLenList, IP, sockSon);
    }
    close(sockFd);
    return NULL;
}

pthread_t CreateConnect(LinkList **list, int num) {
    pthread_t thread;
    arg.list = list;
    arg.listNum = num;

    if (pthread_create(&thread, NULL, (void *)startListen, NULL)) {
        perror("listenGetIP : \033[1;31mcreate thread error\033[0m");
        return -1;
    }

    return thread;
}


int main() {
    pid_t masterPID = fork();
    if (masterPID < 0) {
        perror("main(Fork)");
        return 1;
    } else if (masterPID == 0) {
                
        /* 重定向错误信息到运行日志 */
        if (freopen(RUN_LOG_MASTER, "a", stderr) == NULL) {
            perror("main (freopen)");
            exit(1);
        }
        
        if (freopen("/home/bicheng/Desktop/SHMS-master/print", "a", stdout) == NULL) {
            perror("main (freopen)");
            exit(1);
        }
        
        if (masterConnect()) {
            perror("masterConnect error!");
            return 1;
        }
    } else {
        const char PIDFile[] = "/etc/SHMS-master/master.pid";
        FILE *fp = fopen(PIDFile, "w");
        if (fp == NULL) {
            perror("main(open PIDFile)");
            return 1;
        }
        if (fprintf(fp, "%d", masterPID) < 0) {
            fclose(fp);
            perror("main(write pid to PIDFile)");
            return 1;
        }
        fclose(fp);
    
    }
    
    return 0;
}
