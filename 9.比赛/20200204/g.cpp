/*************************************************************************
	> File Name: g.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月04日 星期二 13时47分44秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int minans = n, end = n;
    int a[26] = {0};
    vector<char> v;
    while(n--) {
        char x;
        cin >> x;
        v.push_back(x);
        a[x - 'a'] ++;
    }
   
    for (int i = 0; i < 26; i++) {
        if (a[i] >= k) {
            vector<int> ans;
            for (int j = 0; j < v.size(); j++) {
                if (v[j] - 'a' == i) ans.push_back(j);
            }
            for (int j = 0; j < ans.size() - k + 1; j++) {
                int temp = ans[j + k - 1] - ans[j] + 1;
                if (temp < minans) {
                    minans = temp;
                }
            }
        }
    }
    if (minans == end) cout << -1 << endl;
    else cout << minans << endl;
    return 0;
}

