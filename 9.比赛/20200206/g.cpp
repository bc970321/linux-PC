/*************************************************************************
	> File Name: g.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月06日 星期四 13时59分24秒
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int T;
    cin >> T;
    while(T--) {
        int a, b, c, d, e, f, g;
        cin >> a >> b >> c >> d >> e >> f >> g;
        a %= 10;
        b %= 10;
        c %= 10;
        g %= 10;
        int ans = (pow(a, b) + pow(b, e) + pow(c, f));
        ans %= 10;
        if (g == ans) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
