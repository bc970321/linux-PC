/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 00时53分53秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <vector>
using namespace std;

int biserach(vector<int> & wa, int & key) {
    int head = -1, tail = wa.size() - 1;
    while(head < tail) {
        int mid = (head + tail + 1) >> 1;
        if (key >= wa[mid]) head = mid;
        else tail = mid - 1;
    }
    return head;
}

int main() {
    map<int, int> mp;
    int n, m, a, b, peo;
    vector<int> ans;
    vector<int>wa, wb;
    cin >> n >> m;
    while(n--) {
        cin >> a >> b;
        if (mp[a] < b) mp[a] = b;
    }
    int max = 0;
    for (auto &x : mp) {
        if (max < x.second) max = x.second;
        else {
            x.second = max;
        }
        wa.push_back(x.first);
    }
    while(m--) {
        cin >> peo;
        int ind = biserach(wa, peo);
        if (ind != -1) cout << mp[wa[ind]] << endl;
        else cout << 0 << endl;
    }
    return 0;
}
