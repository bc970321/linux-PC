/*************************************************************************
	> File Name:    sushu.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年03月24日 星期日 08时12分26秒
 ************************************************************************/

#include<stdio.h>
#include <inttypes.h>

#define MAX_N 10000

int32_t prime[MAX_N + 5] = {0};

int32_t main() {
    for(int i = 2; i <= MAX_N; i++) {
        if(!prime[i]) 
            prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0]; j++) {
            if(i * prime[j] > MAX_N) break;
            prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    int n;
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++) 
            printf("%d ", prime[i]);
        printf("\n");
    }

    return 0;
}
