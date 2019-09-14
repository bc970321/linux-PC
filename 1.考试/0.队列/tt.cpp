/*************************************************************************
	> File Name:    tt.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月17日 星期三 20时14分23秒
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

#define MAX_N 300000
int a[MAX_N + 5];

int main() {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += a[i - 1];
            //cout << a[i] << " ";
            //if (i % 5 == 0) cout << endl;
        }
        int ans = -9999;
        for (int i = 1; i <= m; i++) {
            if (a[i] > ans) ans = a[i];
        }
        for (int i = n; i >= m; i--) {
            a[i] -= a[i - m];
            if (a[i] > ans) {
                ans = a[i];
                //cout << i << " : " << a[i];
                //cout << "ans : " << ans << endl;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
