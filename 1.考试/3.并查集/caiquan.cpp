/*************************************************************************
	> File Name:    caiquan.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 10时50分16秒
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
#define MAX_N 10000
struct UnionSet {
    int fa[MAX_N + 5], val[MAX_N + 5], n;
    void init(int n) {
        this->n = n;
        for (int i = 1; i <= n; i++) fa[i] = i, val[i] = 0;
    }
    int get(int x) {
        if (fa[x] == x) return x;
        int ret = get(fa[x]);
        val[x] += val[fa[x]];
        val[x] %= 3;
        return fa[x] = ret;
    }
    void merge(int a, int b, int c) {
        int aa = get(a), bb = get(b);
        if (aa == bb) return ;
        fa[aa] = bb;
        val[aa] = (val[b] - val[a] + c + 3) % 3;
        return ;
    }
    void output() {
        for (int i = 1; i <= n; i++) {
            cout << i << " : (" << fa[i] << " " << val[i] << ")" << endl;
        }
        return ;
    }
};

int main() {
    int n, m;
    UnionSet u;
    cin >> n >> m;
    u.init(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            u.merge(b, c, 1);
        } else {
            if (u.get(b) != u.get(c)) {
                cout << "Unknown" << endl;
                continue;
            }
            switch ((u.val[b] - u.val[c] + 3) % 3) {
                case 0: cout << "Tie" << endl; break;
                case 1: cout << "Win" << endl; break;
                case 2: cout << "Loss" << endl; break;
            }
        }
    }
    return 0;
}


