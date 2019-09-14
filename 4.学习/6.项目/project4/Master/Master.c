/*************************************************************************
	> File Name: Master.c
	> Author: 
	> Mail: 
	> Created Time: 2019年03月09日 星期六 18时09分47秒
 ************************************************************************/

#include "../common/mainMaster.h"




//心跳函数
int heart(Node_client * client){
    if ((client->fd_client = socket(AF_INET,SOCK_STREAM,0)) < 0){
    perror("socket");
    return -1;
    }

    client->dest_addr.sin_family = AF_INET;
    client->dest_addr.sin_port = htons(client->master_port);
    client->dest_addr.sin_addr.s_addr = inet_addr(client->master_host);
    if (connect(client->fd_client, (struct sockaddr *)&(client->dest_addr),sizeof(client->dest_addr)) < 0){
    printf("%d",__LINE__);
    perror("connect");
    close(client->fd_client);
    return -1;
    }
    //ｍａｓｔｅｒ处理方案是，如果有这个节点的信息就不插入，没有就进行插入
    //因为目的只是让ｍａｓｔｅｒ存储信息所以可以直接进行关闭
    close(client->fd_client);
    return 0;
}






















int main() {
    char *config = "./pihealthd.conf";
    int start[4];    
    int finish[4];
    char start_ip[20] = {0};
    char finish_ip[20] = {0};
    char port_t[6] = {0};
    char port_m[6] = {0};
    char ins_s[5] = {0};
    int ins = 0, port, port_M;
    pthread_t print_t, heart_t;

    get_conf_value(config, "INS", ins_s);
    get_conf_value(config, "From", start_ip);
    get_conf_value(config, "To", finish_ip);
    get_conf_value(config, "client_port", port_t);
    get_conf_value(config, "master_port", port_M);


    ins = atoi(ins_s);
    port = atoi(port_t);
    port_M = atoi(port_m);
    transip(start_ip, start);
    transip(finish_ip, finish);
    
    int *sum = (int *)malloc(ins * sizeof(int));
    
    memset(sum, 0, ins * sizeof(int));

    DBG("start = %d.%d.%d.%d\n", start[0], start[1], start[2], start[3]);
    DBG("finish = %d.%d.%d.%d\n", finish[0], finish[1], finish[2], finish[3]);
    
    LinkedList *linkedlist = (LinkedList *)malloc(sizeof(LinkedList) * ins);

    struct sockaddr_in initaddr;
    initaddr.sin_family = AF_INET;
    initaddr.sin_port = htons(port);
    initaddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    for (int i = 0; i < ins; i++) {
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = initaddr;
        p->next = NULL;
        linkedlist[i] = p;
    }
    
    printf("%s\n", inet_ntoa(linkedlist[0]->client_addr.sin_addr));
    char host[20] = {0};

    for (int i = start[3]; i <= finish[3]; i++) {
        sprintf(host, "%d.%d.%d.%d", start[0], start[1], start[2], i);
        initaddr.sin_addr.s_addr = inet_addr(host);
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = initaddr;
        p->next = NULL;
        int sub = find_min(sum, ins);
        
        insert(linkedlist[sub], p);
        sum[sub]++;
    }
    printf("before pthread_create\n");

    fflush(stdout);
   
    struct HEART heartarg;
    heartarg.head = linkedlist[0];
    heartarg.ins = ins;
    heartarg.sum = sum;
    

    

    if (pthread_create(&heart_t, NULL, heartbeat, (void *)&heartarg) == -1) {
        DBG("error in pthread_create for heartarg\n");
    }

    struct PRINT print_para[ins];
    pthread_t t[ins];
    for (int i = 0; i < ins; i++) {
        print_para[i].index = i;
        print_para[i].head = linkedlist[i];
        if (pthread_create(&t[i], NULL, print, (void *)&print_para[i]) == -1) {
            DBG("error in pthread_create!\n");
            return -1;
        }
    }

    int server_listen;
    if ((server_listen == sockaddr_create(port_M)) < 0) {
        DBG("%s\n", strerror(error));
        close(server_listen);
        return 1;
    }

    while(1) {
        int fd;
        struct sockaddr_in client_addr;
        if((fd == accept(server_listen, (struct sockaddr *)&client_addr, sizeof(client_addr))) < 0) {
            DBG("%s\n", strerror(error));
            close(fd);
            continue;
        }
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = client_addr;
        p->next = NULL;
        int sub = find_min(sum, ins);
        insert(linkedlist[sub], p);
    }



    for (int i = 0; i < ins; i++) {
        pthread_join(t[i], NULL);
    }
    pthread_join(print_t, NULL);
    return 0;
}

