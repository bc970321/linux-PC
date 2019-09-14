/*************************************************************************
	> File Name:    1025.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月25日 星期六 19时54分55秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_N 200
#define MAX_K 6

int f[MAX_N + 5][MAX_K + 5];

int main() {
    int n, k;
    cin >> n >> k;
    f[1][1] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            if(j > i) break;
            f[i][j] = f[i - 1][j - 1] + f[i - j][j];
        }
    }
    cout << f[n][k] << endl;
    return 0;
}

