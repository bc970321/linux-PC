/*************************************************************************
	> File Name: B.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月13日 星期四 23时04分48秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    while(n--) {
        int k;
        cin >> k;
        vector<int> v;
        int input, fushu = 0;
        for (int i = 0; i < k; i++) {
            cin >> input;
            v.push_back(input);
            if (input == -1) fushu++;
        }
        int ans1, ans2;
        if (fushu == k) {
            ans1 = 0, ans2 = 0; 
        }
        if (fushu == k - 1) {
            int myadd = 0;
            for (int i = 0; i < v.size(); i++) {
                if (v[i] != -1) myadd += v[i];
            }
            ans1 = 0, ans2 = myadd;
        }
        int ans = -1, z = 0, tmp = 0;
        if (fushu < k - 1) {
            int min = k + 1, temp = -1, p, q;
            for (int i = 0; i < v.size(); i++) {
                if (v[i] != -1) {
                    if (temp == -1) {
                        temp = i;
                        tmp = 0;
                    } else {
                        min = min < (i - temp) ? min : (i - temp);
                        if (min == i - temp) {
                            p = i, q = temp - tmp;
                        }
                        temp = i;
                        if (min == 1) {
                            tmp++;
                            ans = ans > (tmp - 1) ? ans : (tmp - 1);
                        } else {
                            tmp = 0;
                        }
                    }
                }
            }
            if (min == 1) {
                ans1 = abs(v[p] -v[q]);
                int w = ans1 % ans;
                ans1 = ans1 / ans + (w == 0 ? 0 : 1);
                ans2 = v[p] > v[q] ? v[p] - ans1 : v[q] - ans1;
            } else {
                ans1 = abs(v[p] - v[q]);
                int w = ans1 % 2;
                ans1 = ans1 / 2 + w;
                ans2 = v[p] > v[q] ? v[q] + ans1 : v[p] + ans1;
            }
        }
        cout << ans1 << " " << ans2 << endl;
    }
}
