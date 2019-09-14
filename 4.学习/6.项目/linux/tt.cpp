/*************************************************************************
	> File Name:    tt.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月25日 星期四 15时05分02秒
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
    int n, m;
    int ans = 0;
    for (int i = 3; i <= 10000; i++) {
        if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
        ans += i;
    }
    cout << ans << endl;
    return 0;
}
