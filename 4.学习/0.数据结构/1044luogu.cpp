/*************************************************************************
	> File Name:    4.stack.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月14日 星期日 14时10分41秒
 ************************************************************************/
#include <stdio.h>

int n, f[20][20];

int dfs(int x, int y) {
    if(f[x][y] != 0) return f[x][y];
    if(x == 0) return 1;
    if(y > 0) f[x][y] += dfs(x, y - 1);
    f[x][y] += dfs(x - 1, y + 1);
    return f[x][y];
}


int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", dfs(n, 0));
    return 0;
}
