/*************************************************************************
	> File Name:    client1.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月16日 星期六 16时33分52秒
 ************************************************************************/
#include "client.h"
#include "../common/common.c"

struct sm_msg {
    int flag;//检测次数
    int sm_time;
    pthread_mutex_t sm_mutex;//加锁
    pthread_cond_t sm_ready;//解锁
};

char *config = "./pihealth.conf";//配置信息
char *share_memory = NULL;
char log_dir[50] = {0};
char log_backup[50] = {0};
double dyaver;
int Max_KeepAlive_Interval = 0;
int ctrlport;
int sock_ctrl;

struct sm_msg *msg;

//互斥锁
pthread_mutexattr_t m_attr;
pthread_condattr_t c_attr;

//心跳函数

/*int heart(Node_client * client){
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
    //ｍａｓｔｅｒ处理方案是，如果有这个节点的信息就不插入，如果没有就进行插入，会构建链接，
    //因为目的只是让ｍａｓｔｅｒ存储信息所以可以直接进行关闭
    close(client->fd_client);
    return 0;
}
*/
void sys_detect(int type) {
    int time_i = 0;
    char src[50] = {0};
    sprintf(src, "Src%d", type);
    char run[50] = {0};
    char buffer[4096] = {0};
    get_conf_value(config, src, src);
    FILE *fstream = NULL;
    int times = 0;
    int Inactive_Interval = 0;
    char temp[4] = {0};
    char logname[50] = {0};
    get_conf_value(config, "WriteEveryTimes", temp);
    times = atoi(temp);
    get_conf_value(config, "Inactive_Interval", temp);
    Inactive_Interval = atoi(temp);

    switch(type) {
        case 100://cpu
            time_i = 5;
            sprintf(logname, "%s/cpu.log", log_dir);
            break;
        case 101://mem
            time_i = 5;
            sprintf(logname, "%s/mem.log", log_dir);
            break;
        case 102://disk
            time_i = 60;
            sprintf(logname, "%s/disk.log", log_dir);
            printf("logname = %s/disk.log", log_dir);
            break;
        case 103://pro
            time_i = 30;
            sprintf(logname, "%s/pro.log", log_dir);
            break;
        case 104://sysinfo
            time_i = 60;
            sprintf(logname, "%s/sys.log", log_dir);
            break;
        case 105://userinfo
            time_i = 60;
            sprintf(logname, "%s/user.log", log_dir);
            break;
    }

    sprintf(run, "bash ./script/%s", src);
    if (type == 101) sprintf(run, "bash ./script/%s %lf", src, dyaver);
    while (1) {

        for (int i = 0; i < times; i++) {
            char buff[400] = {0};
            if (NULL == (fstream = popen(run, "r"))) {
                DBG("popen error!\n");
                exit(1);
            }
            if (type == 101) {
                if (NULL != fgets(buff, sizeof(buff), fstream)) {
                    strcat(buffer, buff);
                }
                if (fgets(buff, sizeof(buff), fstream) == NULL) {
                    dyaver = atof(buff);
                } else {
                    dyaver = 0;
                }
            } else {
                while (NULL != fgets(buff, sizeof(buff), fstream)) {
                    strcat(buffer, buff);
                }
            }
        sleep(time_i);
        pclose(fstream);
            if(type = 100) {
                DBG("\033[31m*\033[0m ");
                fflush(stdout);
                pthread_mutex_lock(&msg->sm_mutex);
                if(msg->flag++ >= Inactive_Interval - 1) {
                    if(msg->sm_time == 0) {
                        DBG("\n系统自检超过 \033[33m%d\033[0m 次，Master 无链接\n", msg->flag);
                        pthread_cond_signal(&msg->sm_ready);
                        DBG("发送信号，开启心跳程序 \n");
                    }
                    msg->flag = 0;
                }
                pthread_mutex_unlock(&msg->sm_mutex);
            }
        }
        FILE *fd = fopen(logname, "a+");
        if (NULL == fd) {
            DBG("Error open logfile!\n");
            exit(1);
        }
        if (flock(fd->_fileno, LOCK_EX) < 0) {
            DBG("flock : %s\n", strerror(errno));
        }
        fwrite(buffer, 1, strlen(buffer), fd);
        fclose(fd);
    }
}

bool client_heart(char *ip, int port) {
    bool ret = true;
    int fd;
    if ((fd = socket_connect(port, ip)) < 0) {
        ret = false;
    }
    close(fd);
    return ret;
}

int main() {
    int shmid;
    int heat_listen;
    int port_heart, port_master;
    char ip_master[20] = {0};
    char port_temp[5] = {0};
    char ip_dir[20] = {0};
    char ip_backup[20] = {0};

    get_conf_value(config, "ClientPort", port_temp);
    port_heart = atoi(port_temp);
    get_conf_value(config, "MasterPort", port_temp);
    port_master = atoi(port_temp);
    get_conf_value(config, "Master", ip_master);
    get_conf_value(config, "LogDir", ip_dir);
    get_conf_value(config, "BackupLogDir", ip_backup);
    get_conf_value(config, "Max_KeepAlive_Interval", port_temp);
    Max_KeepAlive_Interval =atoi(port_temp);
    get_conf_value(config, "CtrlPort", port_temp);
    ctrlport = atoi(port_temp);
    mkdir(log_dir, 0755);
    mkdir(log_backup, 0755);
    if ((shmid = shmget(IPC_PRIVATE, sizeof(struct sm_msg), 0666|IPC_CREAT)) == -1) {
        DBG("Erroe in shmget: %s\n", strerror(errno));
        return -1;
    }
    if ((share_memory = (char *)shmat(shmid, 0, 0)) == NULL ) {
       
        DBG("shmat : %s\n", strerror(erroe));
        return -1;
    }
    msg = (struct sm_msg *)share_memory;
    msg->flag = 0;
    msg->sm_time = 0;
    pthread_mutexattr_init(&m_attr);
    pthread_condattr_init(&c_attr);
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);
    
    pthread_mutex_init(&msg->sm_mutex, &m_attr);
    pthread_cond_init(&msg->sm_ready, &c_attr);


    int pid;
    //connect_nonblock(port_master, ip_master, 1);
    
    if ((pid = fork()) < 0) {
        DBG("fork error\n");
        return -1;
    }

    if (pid != 0) { //父进程
        if ((heat_listen = socket_create(port_heart)) < 0) {
            DBG("Error in socket_create!");
            return -1;
        }
        while (1) {
            int fd;
            if ((fd = accept(heat_listen, NULL, NULL)) < 0) {
                DBG("accept error on heart_listen!\n");
                close(fd);
            }
            DBG("\033[35m❤\033[0m");
            fflush(stdout);
            close(fd);
        }
    } else {
        int pid1;//儿子进程
        if ((pid1 = fork()) < 0) {
            DBG("fork error pid1!\n");
            return -1;
        }
        if (pid1 == 0) {
            while (1) {
                pthread_mutex_lock(&msg->sm_mutex);
                DBG("孙子进程等待信号开启心跳！\n");
                pthread_cond_wait(&msg->sm_ready, &msg->sm_mutex);
                DBG("获得心跳信号，开始心跳  ❤\n");
                pthread_mutex_unlock(&msg->sm_mutex);
                while(1) {
                    
                
                    if (client_heart(ip_master, port_master)) {
                        DBG("\n第 %d 次：❤  √  \n", msg->sm_time);
                        pthread_mutex_lock(&msg->sm_mutex);
                        msg->sm_time = 0;
                        pthread_mutex_unlock(&msg->sm_mutex);
                        fflush(stdout);
                    }
                    sleep(6 * msg->sm_time);
                    if (msg->sm_time > Max_KeepAlive_Interval) msg->sm_time = Max_KeepAlive_Interval;
                    pthread_mutex_unlock(&msg->sm_mutex);
                }

            }
        } else {
            int x = 0;
            int pid2; //孙子进程
            for (int i = 100; i < 106; i++) {
                x = i;
                if ((pid2 = fork()) < 0) {
                    DBG("error fork pid2!\n");
                    continue;
                }
                if (pid2 == 0) break;
            }
            if (pid2 == 0) {
                sys_detect(x);
            } else {
                DBG("Father!\n");
                int client_listen;
                if ((client_listen = socket_create(ctrlport)) < 0) {
                    DBG("create client_listen error : %s\n", strerror(errno));
                }
                while (1) {
                    if ((sock_ctrl = accept(client_listen, NULL, NULL)) < 0) {
                        DBG("Error accept client_listen : %s\n", strerror(errno));
                        continue;
                    }
                    DBG("\033[35m❀\033[0m");
                    fflush(stdout);
                    pthread_mutex_lock(&msg->sm_mutex);
                    msg->flag = 0;
                    pthread_mutex_unlock(&msg->sm_mutex);
                    close(sock_ctrl);
                }
            }
        }
    }  
    return 0;
}
