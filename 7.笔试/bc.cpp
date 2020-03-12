/*************************************************************************
	> File Name:    bc.cpp
	> Author:       sunowsir
	> Mail:         sunow.wang@gmail.com
	> Created Time: 2019年10月16日 星期三 21时27分34秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
int main() {
    int a[26] = {0};
    string str;
    cin >> str;
    int ll = str.size();

    for (int i = 0; i < ll; i++) {
        a[str[i] - 'A'] = i;
    }
    int k = a[str[0] - 'A'];
    int ans = 1;
    for (int i = 0; i <= k && i < ll; i++) {
        if (i == k) {
            cout << ans;
            if (k == (ll - 1)) {
                cout << endl;
                break;
            }
            else {
                cout << " ";
                ans = 0;
                k = a[str[i + 1] - 'A'];
            }
        }
        ans ++;
        if (a[str[i] - 'A'] > k) k = a[str[i] - 'A'];
    }

    return 0;
}
