/*************************************************************************
	> File Name:    22.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年09月12日 星期四 10时35分42秒
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


int main() {
    char a[100006];
    cin >> a;
    //cout << a << endl;
    
    int ans = 0;
    int l = strlen(a);
    //cout << l << endl;
    
    int flag = 0, qian = -1, zuo = 0;
    for (int i = 0; i < l; i++) {
        if (!flag) {
            if (a[i] >= '0' && a[i] <= '9') {
                flag = 1;
                qian = a[i] - '0';
                zuo = i;
            }
        } else {
            if (a[i] >= '0' && a[i] <= '9') {
                continue;
            }
            else if (a[i] != ',') {
                flag = 0;
            } else {
                if (i - zuo - 1> 1 && (a[i] - '0') + qian > 8) {
                    ans ++;
                }
                flag = 0;
                qian = -1;
                zuo = 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
