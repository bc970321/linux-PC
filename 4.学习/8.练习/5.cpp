/*************************************************************************
	> File Name: 5.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 23时38分33秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    long long int n, k, ans = 0;
    cin >> n >> k;
    ans = (n - k + 1) * (n - k) / 2;
    for (int i = k + 1; i <= n; i++) {
        ans += (n - i) / i * (i - k) + ((n - i) % i > k ? (n - i) % i - k : 0);
    }
    cout << ans << endl;
    return 0;
}
