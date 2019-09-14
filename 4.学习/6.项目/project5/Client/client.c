/*************************************************************************
	> File Name:    client.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月04日 星期四 16时07分53秒
 ************************************************************************/
#include "./common/common.h"
#include <pthread.h>

struct sm_msg {
    int flag;//检测次数
    int sm_time;
    pthread_mutex_t sm_mutex;//锁
    pthread_cond_t sm_ready;//信号量
};

char *config = "./script/PiHealth.conf";//配置文件
char *share_memory = NULL;
char log_dir[50] = {0};
char log_backup[50] = {0};
double dyaver = 0;
int Max_KeepAlive_Interval = 0;
int ctrlport;
int sock_ctrl;

struct sm_msg *msg;

pthread_mutexattr_t m_attr;
pthread_condattr_t c_attr;

void sys_detect(int type) {
    int time_i = 0;
    char temp_sc[20] = {0};
    char src[50] = {0};
    sprintf(temp_sc, "Scr%d", type);
    char run[100] = {0};
    char buffer[4096] = {0};
    char port_temp[5] = {0};
    get_conf_value(config, temp_sc, src);
    FILE *fstream = NULL;
    int times = 0;
    int Inactive_Interval = 0;
    char temp[4] = {0};
    char logname[50] = {0};
    get_conf_value(config, "WriteEveryTimes", temp);
    times = atoi(temp);
    get_conf_value(config, "Inactive_Interval", temp);
    Inactive_Interval = atoi(temp);

    switch(type) {//将.log文件中的内容存到logname中
        case 100://cpu
            time_i = 5;
            sprintf(logname, "%s/cpu.log", log_dir);//log_dir log 目录
            break;
        case 101://mem
            time_i = 5;
            sprintf(logname, "%s/mem.log", log_dir);
            break;
        case 102://disk
            time_i = 60;
            sprintf(logname, "%s/disk.log", log_dir);
            break;
        case 103://pro
            time_i = 30;
            sprintf(logname, "%s/pro.log", log_dir);
            break;
        case 104://sysinfo
            time_i = 60;
            sprintf(logname, "%s/sysinfo.log", log_dir);
            break;
        case 105://userinfo
            time_i = 60;
            sprintf(logname, "%s/userinfo.log", log_dir);
            break;
    }
    sprintf(run, "bash ./script/%s", src);//将需要执行的命令存入run
    
    if (type == 101) sprintf(run, "bash ./script/%s %f", src, dyaver);
    while (1) {
        for (int i = 0; i <= times; i++) {
            char buff[400] = {0};
            if (NULL == (fstream = popen(run, "r"))) {//执行run里面的执行脚本命令
                DBG("popen error!\n");
                exit(1);
            }
            fstream = popen(run, "r");
            fgets(buff, sizeof(buff), fstream);
            if (type == 101) {
                if (NULL != fgets(buff, sizeof(buff), fstream)) {//存进buff数组内
                    strcat(buffer, buff);//将buff中的内容复制到buffer内
                }
                if (NULL != fgets(buff, sizeof(buff), fstream)) {
                    dyaver = atof(buff);//将字符串转化为浮点数
                } else {
                    dyaver = 0;
                }
            } else {
                do {
                    strcat(buffer, buff);
                } while (NULL != fgets(buff, sizeof(buff), fstream));
            }
            sleep(time_i);
            pclose(fstream);//与popen对应 关闭
            if (type == 100) {
                DBG("\033[31m*\033[0m ");
                fflush(stdout);
                pthread_mutex_lock(&msg->sm_mutex);//加锁 占有互斥锁 阻塞
                if (msg->flag++ >= Inactive_Interval - 1) {
                    if (msg->sm_time == 0) {
                        DBG("\n系统自测超过 \033[3m%d\033[0m 次, Master 无连接\n", msg->flag);
                        pthread_cond_signal(&msg->sm_ready);//解锁
                        DBG("发送信号, 开启心跳程序 ❤\n");
                    }
                    msg->flag = 0;
                }
                pthread_mutex_unlock(&msg->sm_mutex);//解锁
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
        fwrite(buffer, 1, strlen(buffer), fd);//将buffer存入 logname内的字符串为名的文件内
        fclose(fd);
    }
}

int main() {
    int shmid;
    int heat_listen;
    int port_heart, port_master;
    char ip_master[20] = {0};
    char port_temp[5] = {0};

    get_conf_value(config, "ClientPort", port_temp);//获取配置文件信息
    port_heart = atoi(port_temp);
    get_conf_value(config, "MasterPort", port_temp);
    port_master = atoi(port_temp);
    get_conf_value(config, "Master", ip_master);
    get_conf_value(config, "LogDir", log_dir);
    get_conf_value(config, "Backup", log_backup);
    get_conf_value(config, "Max_KeepAlive_Interval", port_temp);
    Max_KeepAlive_Interval = atoi(port_temp);
    get_conf_value(config, "CtrlPort", port_temp);
    ctrlport = atoi(port_temp);
    mkdir(log_dir, 0755);//创建一个目录给其可读写权限
    mkdir(log_backup, 0755);
    
    if ((shmid = shmget(IPC_PRIVATE, sizeof(struct sm_msg), 0666|IPC_CREAT)) == -1) {
        //得到一个共享内存标识符或创建一个共享内存对象并返回共享内存标识符
        DBG("Erroe in shmget: %s\n", strerror(errno));
        return -1;
    }

    if ((share_memory = (char *)shmat(shmid, 0, 0)) == NULL ) { //连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问
        DBG("shmat : %s\n", strerror(erroe));
        return -1;
    }

    msg = (struct sm_msg *)share_memory;
    msg->flag = 0;
    msg->sm_time = 0;
    pthread_mutexattr_init(&m_attr);//初始化互斥锁属性对象
    pthread_condattr_init(&c_attr);//初始化条件变量
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);//设置互斥锁范围
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);

    int pid;
    connect_nonblock(port_master, ip_master, 1);//阻塞
    
    if ((pid = fork()) < 0) {
        DBG("fork error\n");
        return -1;
    }

    if (pid != 0) {//父进程
        if ((heat_listen = socket_create(port_heart)) < 0) {//创建并返回一个套接字
            DBG("Error in socket_create!");
            return -1;
        }
        while (1) {
            int fd;
            if ((fd = accept(heat_listen, NULL, NULL)) < 0) {//接收连接
                DBG("accept error on heart_listen!\n");
                close(fd);
            }
            int number;
            number = recv_response(heat_listen);//返回接收到的序号
            if (number >= 100 && number < 106) {
                send_response(number, heat_listen);//根据序号发送文件
            }
            DBG("\033[35m❤\033[0m");
            fflush(stdout);
            close(fd);
        }
    } else {//子进程
        int pid1;
        if ((pid1 = fork()) < 0) {
            DBG("fork error pid1!\n");
            return -1;
        }
        if (pid1 == 0) {//孙子进程
            while (1) {
                pthread_mutex_lock(&msg->sm_mutex);//加一个锁 占有互斥锁 阻塞操作
                DBG("孙子进程等待信号开启心跳！\n");
                pthread_cond_wait(&msg->sm_ready, &msg->sm_mutex);//等待条件变量的特殊条件发生
                DBG("获得心跳信号, 开始心跳   \n");
                pthread_mutex_unlock(&msg->sm_mutex);//释放互斥锁
                while(1) {
                    if (client_heart(ip_master, port_master)) {//心跳
                        DBG("第%d次：√!\n"msg->sm_time);
                        pthread_mutex_lock(&msg->sm_mutex);//占有互斥锁 阻塞
                        msg->sm_time = 0;
                        msg->flag = 0;
                        pthread_mutex_unlock(&msg->sm_mutex);//释放互斥锁
                        fflush(stdout);
                        break;
                    } else {
                        DBG("\n第%d次：❤ ×\n", msg->sm_time);
                        pthread_mutex_lock(&msg->sm_mutex);//占有互斥锁 阻塞
                        msg->sm_time++;
                        pthread_mutex_unlock(&msg->sm_mutex);//释放互斥锁
                        fflush(stdout);
                    }
                    sleep(6 * msg->sm_time);
                    if (msg->sm_time > Max_KeepAlive_Interval) msg->sm_time = Max_KeepAlive_Interval;
                    pthread_mutex_unlock(&msg->sm_mutex);//释放互斥锁
                }
            }
        } else {//子进程
            int x = 0;
            int pid2;
            for (int i = 100; i < 106; i++) {
                x = i;
                if ((pid2 = fork()) < 0) {
                    DBG("error fork pid2!\n");
                    continue;
                }
                if (pid2 == 0) break;
            }
            if (pid2 == 0) {//孙子进程
                sys_detect(x);//根据x为100到105 执行相关操作
            } else {
                DBG("Father!\n");
                int client_listen;
                if ((client_listen = socket_create(ctrlport)) < 0) {
                    DBG("create client_listen error : %s\n", strerror(errno));
                }
                while(1) {
                    if ((sock_ctrl = accept(client_listen, NULL, NULL)) < 0) {
                        DBG("Error accept client_listen: %s\n", strerror(errno));
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
