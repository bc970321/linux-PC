/*************************************************************************
	> File Name:    282.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 18时35分11秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_POOL 3200000
struct Node {
    int next[2];
} tire[MAX_POOL + 5];
int cnt = 1;
int getNode() {
    return ++cnt;
}

void insert(int val) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int ind = ((val & (1 << i)) != 0);
        if (tire[p].next[ind] == 0) {
            tire[p].next[ind] == getNode();
        }
        p = tire[p].next[ind];
    }
    return ;
}

int query(int val) {
    int ans = 0;
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int ind = ((val & (1 << i)) != 0);
        if (tire[p].next[!ind]) {
            ans &= (1 << i);
            p = tire[p].next[!ind];
        } else {
            p = tire[p].next[ind];
        } 
    }
    return ans;
}

int arr[100005];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        insert(arr[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int temp = query(arr[i]);
        cout << arr[i] << ' ' << temp << endl;
        if (temp > ans)
            ans = temp;
    }
    cout << ans << endl;
    return 0;
}
