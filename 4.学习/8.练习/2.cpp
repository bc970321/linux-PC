/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 01时04分33秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int l, r;
    cin >> l >> r;
    int ans = 0, val = 0;
    for (int i = 1; i < l; i++) {
        ans += i;
    }
    for (int i = l; i <= r; i++) {
        ans += i;
        if (ans % 3 == 0) {
            val++;
        }
        ans %= 3;
    }
    cout << val << endl;
    return 0;
}
