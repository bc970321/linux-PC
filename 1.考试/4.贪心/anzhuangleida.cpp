/*************************************************************************
	> File Name:    anzhuangleida.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 10时52分51秒
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
#define MAX_N 1000
struct Range {
    double l, r;
} arr[MAX_N + 5];

bool cmp(const Range &a, const Range &b) {
    return a.r < b.r;
}

int main() {
    int n;
    double d;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        if (y > d) {
            cout << -1 << endl;
            return 0;
        }
        arr[i].l = x - sqrt(d * d - y * y);
        arr[i].r = x + sqrt(d * d - y * y);
    }
    sort(arr, arr + n, cmp);
    double p = arr[0].r;
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i].l > p) {
            cnt += 1;
            p = arr[i].r;
        }
    }
    cout << cnt << endl;
    return 0;
}
