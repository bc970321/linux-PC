/*************************************************************************
	> File Name:    1057.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月25日 星期六 20时28分00秒
 ************************************************************************/

#include<iostream>
using namespace std;

long long int f[35][35];

int main() {
    int n, m;
    cin >> n >> m;
    f[0][1] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j - 1] + f[i - 1][j + 1];
            if(j == 1) f[i][j] += f[i - 1][n];
            if(j == n) f[i][j] += f[i - 1][1];
        }
    }
    cout << f[m][1] << endl;
    return 0;
}
