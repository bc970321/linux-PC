/*************************************************************************
	> File Name:    222.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年09月09日 星期一 19时29分31秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        int ans = 1;
        for (int i = 2; i <= n / 2; i++) {
            if (i % 2 == 1) {
                if (n % 2 == 0) {
                    ans += 1;
                }
            } else if (i % 2 == 0) {
                if (n % 2 == 1) {
                    ans += 1;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}


