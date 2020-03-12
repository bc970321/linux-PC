/*************************************************************************
	> File Name: e.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 13时16分50秒
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int func(int x) {
    int ans = 0, s = (int)sqrt(x);
    for (int i = 1; i <= s; i++) {
        if (x % i == 0) {
            ans += 2;
        }
    }
    if (s * s == x) return ans - 1;
    else return ans;
}

int main() {
    int n;
    cin >> n;
    int ans = 1, k = func(n);
    while(k != 2) {
        k = func(k);
        ans ++;
    }
    cout << ans << endl;
    return 0;
}
