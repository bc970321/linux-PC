/*************************************************************************
	> File Name:    1028.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月25日 星期六 20时04分23秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_N 1000

int f[MAX_N + 5];

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i / 2; j++) {
            f[i] += f[j];
        }
        f[i]++;
    }
    cout << f[n] << endl;
    return 0;
}


