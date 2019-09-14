/*************************************************************************
	> File Name:    11.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年09月12日 星期四 10时30分27秒
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

long long int zz(int m, int k) {
    long long int ans = k;
}

int main() {
    int m, k;
    while(scanf("%d%d", &m, &k) != EOF) {
        switch(m) {
            case 0: {
                printf("0\n");
            } break;
            case 1: {
                printf("%d\n", k);
            } break;
            case 2: {
                printf("%d\n", k * 2 + 2);
            } break;
        
        }
    }
    return 0;
}
