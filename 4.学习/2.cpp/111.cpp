/*************************************************************************
	> File Name:    111.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年09月10日 星期二 19时13分53秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;





int main() {
    char s1[10005], s2[10005];
    cin >> s1;
    cin >> s2;
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int ans = 0;
    for(int i = 0; i < l2; i++) {
        if (s1[i] != s2[i]) {
            ans ++;
        }
    }
    cout << ans << endl;
    return 0;
}
