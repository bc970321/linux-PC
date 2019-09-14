/*************************************************************************
	> File Name:    time.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月19日 星期二 20时35分57秒
 ************************************************************************/

#include <stdio.h>
#include <time.h> 
#include <unistd.h>
int main() {
    time_t t;
    struct tm * lt;
    while(1) {
    time(&t);
    lt = localtime(&t);
    if (lt->tm_sec % 10 == 0) {
        printf("Hello World!\n");
        printf("%d:%d\n",lt->tm_min,lt->tm_sec);
        sleep(9);
        } else 
        sleep(1);
    }
    return 0;
}

