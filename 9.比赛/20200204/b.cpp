/*************************************************************************
	> File Name: b.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 13时08分46秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int n, x, a, b;
    cin >> n >> x >> a >> b;
    double ans = (x * a + (100 - x) * b) / 100.0 * n;
    printf("%.2f\n", ans); 
    return 0;
}
