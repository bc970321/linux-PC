/*************************************************************************
	> File Name:    I.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 18时37分03秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#define MAX_POOL 3200000
struct Node {
    int next[2];
} trie[MAX_POOL + 5];
int cnt = 1;
int getNode() {
    return ++cnt;
}

void insert(int val) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int ind = ((val & (1 << i)) != 0);
        if (trie[p].next[ind] == 0) {
            trie[p].next[ind] = getNode();
        }
        p = trie[p].next[ind];
    }
    return ;
}

int query(int val) {
    int ans = 0;
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int ind = ((val & (1 << i)) != 0);
        if (trie[p].next[!ind]) {
            ans |= (1 << i);
            p = trie[p].next[!ind];
        } else {
            p = trie[p].next[ind];
        }
    }
    return ans;
}

int arr[100005];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i], insert(arr[i]);
    int ans = 0, temp;
    for (int i = 0; i < n; i++) {
        temp = query(arr[i]);
        ans = max(ans, temp);
    }
    cout << ans << endl;
    return 0;
}
