/*************************************************************************
	> File Name:    281.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 18时22分47秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_POOL 1000000
#define max_size 26

struct Node {
    int flag;
    int size[26];
} tire[MAX_POOL + 5];

int cnt = 1;

inline int getNode() {
    return ++cnt;
}

void insert(int ind, const char *str) {
    int p = ind;
    for (int i = 0; str[i]; i++) {
        if (tire[p].size[str[i] - 'a'] == 0) {
            tire[p].size[str[i] - 'a'] = getNode();
        }
        p = tire[p].size[str[i] - 'a'];
    }
    tire[p].flag += 1;
    return ;
}

int query(int ind, const char *str) {
    int p = ind;
    int ans = 0;
    for (int i = 0; str[i]; i++) {
        if(p == 0) break;
        p = tire[p].size[str[i] - 'a'];
        ans += tire[p].flag;
    }
    return ans;
}

char str[MAX_POOL + 5];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> str;
        insert(1, str);
    }
    for (int i = 0; i < m; i++) {
        cin >> str;
        cout << query(1, str) << endl;
    }
    return 0;
}
