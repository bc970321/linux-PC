/*************************************************************************
	> File Name:    255.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 19时48分32秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node {
    double l, r;
} arr[1005];

bool cmp(const Node &a, const Node &b) {
    return a.r < b.r;
}

int main() {
    int n;
    double d;
    double x, y;
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        if(y > d) {
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
