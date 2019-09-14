/*************************************************************************
	> File Name:    7.virtual_table.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月09日 星期二 15时42分53秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

class A {
public : 
    virtual void run(int x) {
        cout << "class A run" << endl;
    }
};

class B : public A{
public:
    void run(int x) {
        cout << "class B run" << endl;
        cout << this << endl;
        cout << x << endl;
    }
};

typedef void (*func)(void *,int);


int main() {
    B b;
    ((func **)(&b))[0][0](&b,123);
    return 0;
}
