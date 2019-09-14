/*************************************************************************
	> File Name:    15.single.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月28日 星期日 16时17分17秒
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

//单例模式
struct SingleClass {
public:
    static SingleClass *getInstance() {
        static SingleClass *obj = nullptr;
        if (obj) return obj;
        obj = new SingleClass();
        return obj;
    }
private:
    SingleClass() {}
    SingleClass(const SingleClass &) {}
};

int main() {
    SingleClass *a = SingleClass::getInstance();
    SingleClass *b = SingleClass::getInstance();
    return 0;
}

