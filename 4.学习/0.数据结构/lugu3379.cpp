/**************************************************************************
    > File Name:    test.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月13日 星期六 18时32分39秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_M 10000
#define MAX_N 1000
#define MAX_K 32

struct Edge {
    int to, next;
} g[MAX_M + 5];
    
int head[MAX_N + 5] = {0}, cnt = 0;//head数组存的值为g数组下标，起到索引的作用

int gas[MAX_N + 5][MAX_K] = {0}, deep[MAX_N + 5] = {0};

inline void add(int a, int b) { //a为起点，b为终点， 存储的信息为a到b的这条线段 
    g[++cnt].to = b; // 存终端b
    g[cnt].next = head[a]; // next存上一条a为起点的信息的next，也就是head[a]
    head[a] = cnt;//更新head[a] 存这条边在g数组的位置（下标），也就是最后一条以a为起点的信息存在g数组的位置
    return ;//直观上可获取所有输入的线段的信息，可以索引、搜索出以某一点开始出发的所有的边，但在索引全部出来之前并不知到具体数量
}

void dfs1(int fa, int ind) {
    for (int i = 1; i <= MAX_K; i++) {
        gas[ind][i] = gas[gas[ind][i - 1]][i - 1];
    }
    for (int i = head[ind]; i; i = g[i].next) {
        if(g[i].to == fa) continue;
        int to = g[i].to;
        deep[to] = ind + 1;
        gas[to][0] = ind;
        dfs1(ind, to);
    }
    return ;
}

int lca(int x, int y) {
    if (deep[x] < deep[y]) swap(x, y);
    for (int i = MAX_K; i >= 0; i--) {
        if (deep[gas[x][i]] < deep[y]) continue;
        x = gas[x][i];
    }
    if (x == y) return x;
    for (int i = MAX_K; i >= 0; i--) {
        if (gas[x][i] != gas[y][i]) continue;
        x = gas[x][i], y = gas[y][i];
    }
    return gas[x][0];
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    deep[0] = -1;
    dfs1(0, s);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >>a >> b;
        cout << lca(a, b) << endl;
    }
    return 0;
}


