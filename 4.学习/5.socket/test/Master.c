/*************************************************************************
	> File Name: Master.c
	> Author: 
	> Mail: 
	> Created Time: 2019年03月09日 星期六 18时09分47秒
 ************************************************************************/

#include "master.h"




int main() {
    char *config = "/etc/pihealthd.conf";
    int start[4];    
    int finish[4];
    char start_ip[20] = {0};
    char finish_ip[20] = {0};
    char port_t[6] = {0};
    char ins_s[5] = {0};
    int ins = 0;
    pthread

    get_conf_value(config, "INS", ins_s);
    get_conf_value(config, "From", start_ip);
    get_conf_value(config, "To", finish_ip);
    get_conf_value(config, "client_port", port_t);


    ins = atoi(ins_s);
    port = atoi(port_t);
    transip(start_ip, start);
    transip(finish_ip, finish);
    
    int *sum = (int *)malloc(ins * sizeof(int));
    
    memset(sum, 0, sizeof(sum));

    DBG ("%d.%d.%d.%d\n", start[0], start[1], start[2], start[3]);

    LinkedList linkedlist = (LinkedList)malloc(sizeof(LinkedList) * ins);

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
        p->addr = initaddr;
        p->next = NULL;
        int sub = find_min(sum, ins);
        insert(linkedlist[sub], p);
        sub[sub]++;
    }
    printf("before pthread_create\n");

    fflush(stdout);
    
    struct HEART heartarg;
    heartarg.head = linkedlist[0];
    heartarg.ins = ins;
    
    
    struct PRINT print_para[ins];
    pthread_t t[ins];
    for (int i = 0; i < ins; i++) {
        print_para[i].index = i;
    
    }



    pthread_create(&print_t, NULL, print, (void *)linkedlist[0]);

    for (int i = 0; i < ins; i++) {
        printf("sum[%d] = %d\n", i, sum[i]);
    }

    pthread_join(print_t, NULL);
    return 0;
}



