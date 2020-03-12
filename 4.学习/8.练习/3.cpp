/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 23时16分08秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, ans = 0;
        cin >> n;
        string ch;
        cin >> ch;
        for (int i = 0; i < ch.size(); i++) {
            if (ch[i] == '.') {
                i += 2;
                ans ++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

