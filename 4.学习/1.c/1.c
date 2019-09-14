/*************************************************************************
	> File Name:    1.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月21日 星期四 18时10分26秒
 ************************************************************************/

#include<stdio.h>


void myswap(int *a, int *b) {
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

int main() {
    int a = 1;
    int b = 2;
    int *c;
    c = &b;

    myswap(&a, &b);

    printf("%d %d\n", a, b);
    printf("%d\n", *c);
    return 0;
}
