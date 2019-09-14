/*************************************************************************
	> File Name:    dfs2.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月08日 星期三 15时04分56秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_N 1000
int N, M;
char field[MAX_N + 5][MAX_N + 5];


void dfs(int x, int y) {
    field[x][y] = '.';

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int nx = x + i, ny = y + j;
            if (0 <= nx && nx < N && 0 <= ny && ny < M && field[nx][ny] == 'W')
                dfs(nx, ny);
        }
    }
    return ;
}

void solve() {
    int res = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] == 'W') {
                dfs(i, j);
                res++;
                for(int i = 0; i < N; i++) {
                    for(int j = 0; j < M; j++) {
                    printf("%c ", field[i][j]);
                    }
                printf("\n");
                }
                printf("\n\n\n\n");
            }
        }
    }
    printf("%d\n", res);
}


int main() {
    scanf("%d%d", &N, &M);
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= M; j++) {
            scanf("%c", &field[i][j]);
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%c", field[i][j]);
        }
    } 
    solve();
    return 0;
}
