/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 12时59分44秒
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, x, y, a, b;
    cin >> n >> x >> y >> a >> b;
    long long int ans1 = x, ans2 = y, ans3 = 0;
    for (int i = 3; i <= n; i++) {
        ans3 = ans1 * ans2 * pow(a, b);
        ans3 %= 1000000007;
        ans1 = ans2;
        ans2 = ans3;
    }
    if (n == 1) cout << ans1 << endl;
    else cout << ans2 << endl;
    return 0;
}
