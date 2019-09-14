/*************************************************************************
	> File Name:    16.class_pointer.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月28日 星期日 16时46分56秒
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
public:
    void say1() {
        cout << "say 1" << endl;
    }
    void say2() {
        cout << "say 2" << endl;
    }
    void say3() {
        cout << "say 3" << endl;
    }
};

void (A::*func[3])() = {&A::say1, &A::say2, &A::say3};

int main() {
    srand(time(0));
    A a;
    A *p;
    for (int i = 0; i < 20; i++) {
        (a.*func[rand() % 3])();
        (p->*func[rand() % 3])();
    }
    return 0;
}
