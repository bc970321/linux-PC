/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月21日 星期一 19时14分10秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;
#define MAX_N 100000

int ans[1000] = {0};

int main() {
    int input;
    while(scanf("%d", &input) != EOF) {
        ans[input / 100] ++;
    }
    
    for (int i = 0; i < MAX_N / 100; i++) {
        printf("%d-%d %d\n", i * 100, i * 100 + 99, ans[i]);
    }
    return 0;
}
