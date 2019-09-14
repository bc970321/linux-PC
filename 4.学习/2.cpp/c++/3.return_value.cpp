/*************************************************************************
	> File Name:    3.return_value.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月23日 星期日 18时58分08秒
 ************************************************************************/

#include<iostream>
using namespace std;


class A {
public:
    A() {
        cout << "constructor" << endl;
    }
    A(const A &obj) {
        cout << "copy constructor" << endl;
    }
    ~A() {
        cout << "destructor" << endl;
    }
};

A func() {
    A temp;
    return temp;
}

int main() {
    A a(func());
    return 0;
}
