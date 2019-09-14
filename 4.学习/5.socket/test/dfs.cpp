/*************************************************************************
	> File Name:    dfs.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月08日 星期三 14时55分17秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
using namespace std;
#define MAX_N 1000

int a[MAX_N + 5];
int n, k;



bool dfs(int i, int sum) {
    if(i == n) return sum == k;

    if(dfs(i + 1, sum)) return true;
    if(dfs(i + 1, sum + a[i])) return true;
    
    return false;
}


int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &k);

    if(dfs(0, 0)) printf("YES\n");
    else printf("NO\n");
    
    return 0;
}
