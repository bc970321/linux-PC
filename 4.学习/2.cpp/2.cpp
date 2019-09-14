/*************************************************************************
	> File Name:    2.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月21日 星期四 18时39分56秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

//char c[2];

char *aa(char a, char b) {
    char *c;
    c = &a;
    return c;
}

char *t() {
    char x[20] = {0};
    strcpy(x, "hello");
    return x;
}

int main() {
    char a = 'q', b = 'p';
    string w = aa(a, b);

    printf("%s\n", t());
    return 0;
}
