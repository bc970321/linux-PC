/*************************************************************************
	> File Name:    J.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 18时08分57秒
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
long long int a[10005];


int main() {
    long long int n, t = 0, x;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        sort(a, a + i + 1);
        a[0] = a[0] + a[1];
        a[1] = a[i];
        t += a[0];
    }
    cout << t << endl;
    return 0; 
}
