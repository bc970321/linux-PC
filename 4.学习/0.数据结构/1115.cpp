/*************************************************************************
	> File Name:    1115.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月25日 星期六 20时42分15秒
 ************************************************************************/

#include<iostream>
using namespace std;

int a[200005];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    int pre_min = 0, sum = 0, ans = a[0];
    for(int i = 0; i < n; i++) {
        sum += a[i];
        if(sum - pre_min > ans) ans = sum - pre_min;
        if(sum  < pre_min) pre_min = sum;
    }
    cout << ans << endl;

    return 0;
}
