/*************************************************************************
	> File Name: d.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 13时14分03秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int ans = (1 + n) * n / 2;
    while((n--) - 1) {
        int x;
        cin >> x;
        ans -= x;
    }
    cout << ans << endl;
    return 0;
}
