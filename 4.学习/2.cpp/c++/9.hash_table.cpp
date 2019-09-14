/*************************************************************************
	> File Name:    9.hash_table.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月16日 星期二 19时39分04秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <unordered_map>
using namespace std;

struct A {
    A(int x, int y) : x(x), y(y) {}
    int x, y;
    bool operator==(A const &a) const {
        return this->x == a.x && this->y == a.y;
    }
};

struct myhash {
    int operator()(A const &a) const {
    return a.x + a.y;
    }
};


int main() {
    A a(0, 9), b(10, 12);
    unordered_map<A, int, myhash> arr;
    arr[a] = 1;
    arr[b] = 2;
    cout << arr[a] << endl;
    cout << arr[b] << endl;
    return 0;
}
