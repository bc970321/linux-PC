/*************************************************************************
	> File Name:    D.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 19时03分11秒
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

#define MAX_N 500000
int a[MAX_N + 5];

int main() {
    int n, x;
    while(~scanf("%d", &n) && n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        x = 0;
        for (int i = n - 1; i > 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if(a[i] < a[j]) {
                    x++;
                    cout << a[i] << " " << a[j] << endl;
                }
            }
        }
        cout << x << endl;
    }
    return 0;
}
