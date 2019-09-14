/*************************************************************************
	> File Name:    tuzi.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月26日 星期日 14时05分55秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;


int main() {
    int n;
    cin >> n;
    int f[3][1000] = {0};
    f[0][0] = 1;
    f[1][0] = 1;
    f[0][1] = 1;
    f[1][1] = 2;
    for(int i = 2; i < n + 2; i++) {
        for(int j = 1; j <= f[(i - 1) % 3][0]; j++) {
            f[i][j] = f[(i -1) % 3][j] + f[(i - 2) % 3][j];
        }
        for(int j = 1; j <= f[i][0]; j++) {
            if(j != f[i][0]) {
                f[i][j + 1] += f[i][j] / 10;
                f[i][j] %= 10;
            } else {
                if(f[i][j] > 10)
                f[i][0]++;
                j--;
            }
        }
    }
    for(int i = f[n % 3][0]; i >= 1; i--) {
        printf("%d", f[n % 3][i]);
    }
    printf("\n");
    return 0;
}

