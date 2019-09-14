/*************************************************************************
	> File Name:    44.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月26日 星期日 14时58分38秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;
#define MAX_N 500000

int dp[MAX_N + 5]
int val[MAX_N + 5]

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> val[i];
    dp[0] = 1;
    for(int i = 1; i < n; i++) {
        dp[i] = 1;
        for(int j = 0; j < i; j++) {
            if(val[j])
        }
    }

    return 0;
}

