/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 00时08分07秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long int n, m;
    cin >> n >> m;
    vector<long long int> d;
    vector<long long int> p;
    for (int i = 0; i < n; i++) {
        long long int t1, t2;
        cin >> t1 >> t2;
        d.push_back(t1);
        p.push_back(t2);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long long int temp = d[i], val = i;
            if (d[j] < temp) {
                temp = d[j];
                val = j;
            }
            d[val] = d[i];
            d[i] = temp;
            temp = p[val];
            p[val] = p[i];
            p[i] = temp;
        }
    }
    long long int max = p[0];
    for (int i = 1; i < n; i++) {
        if (p[i] < max) {
            p[i] = max;
        } else {
            max = p[i];
        }
    }
    while(m--) {
        long long int a;
        cin >> a;
        if (a < d[0]) cout << 0 << endl;
        for (int i = 1; i < n; i++) {
            if (a >= d[i - 1] && a < d[i]) cout << p[i - 1] << endl;
        }
        if (a >= d[n - 1]) cout << p[n - 1] << endl;
    }
    return 0;
}
