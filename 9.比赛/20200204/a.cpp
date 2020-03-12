/*************************************************************************
	> File Name: a.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 14时45分09秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    long long int n, m, ans = 0;
    cin >> n >> m;
    ans += (n - 2) * (m - 1) * 2 % 1000000007 * n; 
    ans += (m - 2) * (n - 1) * 2 % 1000000007 * m;
    cout << ans << endl;
    return 0;
}
