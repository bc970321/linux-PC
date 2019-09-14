/*************************************************************************
	> File Name:    B.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 18时02分20秒
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

int main() {
    long long int a, b, p;
    cin >> a >> b >> p;
    for (int i = 1; i < p; i++) {
        a *= a;
        a %= p;
    }
    cout << a << endl;
}
