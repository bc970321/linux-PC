/*************************************************************************
	> File Name:    256.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月20日 星期四 19时10分36秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_N 1000

struct Node {
    int l, r, ans;
} chen[MAX_N + 5];

bool cmp(const Node &a, const Node &b) {
    return a.ans < b.ans;
}

int main() {
    int n;
    cin >> n;
    Node huang;
    cin >> huang.l >> huang.r;
    for (int i = 0; i < n; i++) {
        cin >> chen[i].l >> chen[i].r;
        chen[i].ans = chen[i].l * chen[i].r;
    }
    sort(chen, chen + n, cmp);
    int sum = huang.l;
    for (int i = 0; i < n - 1; i++) {
        sum *= chen[i].l;
    }
    cout << sum / chen[n - 1].r << endl;
    return 0;
}
