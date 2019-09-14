/*************************************************************************
	> File Name:    253.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 19时11分07秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX_N 2500

struct node {
    int mi; 
    int ma;
    bool operator<(const node &a)const {
        return ma > a.ma;
    }
} cow[MAX_N + 5], ff;

struct nod {
    int spf, co;
} ss[2505];

bool cmp1(const node &a, const node &b) {
    return a.mi < b.mi;
}

bool cmp2(const nod &a, const nod &b) {
    return a.spf < b.spf;
}

priority_queue<node>que;

int main() {
    int c, l;
    cin >> c >> l;
    for(int i = 0; i < c; i++) {
        cin >> cow[i].mi >> cow[i].ma;
    }
    for(int i = 0; i < l; i++) {
        cin >> ss[i].spf >> ss[i].co;
    }
    sort(cow, cow + c, cmp1);
    sort(ss, ss + l, cmp2);
    int ans = 0, j = 0;
    for (int i = 0; i < l; i++) {
        for( ;j < c; j++) {
            if (ss[j].co == 0) continue;
            if (ss[j].spf < cow[i].mi || ss[j].spf > cow[i].ma) continue;
            if (cow[i].mi <= ss[i].spf)
                que.push(cow[j]);
            else break;
        }
        while (!que.empty() && ss[i].co) {
            ff = que.top();
            que.pop();
            if (ff.ma > ss[i].spf) {
                ans ++;
                ss[i].co--;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
