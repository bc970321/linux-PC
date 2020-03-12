/*************************************************************************
	> File Name: a.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月06日 星期四 13时35分52秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    int ans = (a > y ? a - y : a) + (b > z ? b - z : b) + (c > x ? c - x : c);
    cout << ans << endl;
    return 0;
}
