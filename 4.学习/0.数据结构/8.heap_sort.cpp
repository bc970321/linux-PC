/*************************************************************************
	> File Name:    8.heap_sort.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月27日 星期六 19时32分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp; \
}

#define MAX_N 1000
int num[MAX_N + 5], n;

void update_down(int *num, int ind, int n) {
    while (ind << 1 <= n){
        int temp = ind, lchild = ind << 1, rchild = ind << 1 | 1;
        if (num[temp] < num[lchild]) temp = lchild;
        if (rchild <= n && num[temp] < num[rchild]) temp = rchild;
        if (temp == ind) break;
        swap(num[temp], num[ind]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *num, int n) {
    num -= 1;
    for (int i = n >> 1; i >= 1; i--) update_down(num, i, n);
    for (int i = n; i >= 2; i--) {
        swap(num[i], num[1]);
        update_down(num, 1, i - 1);
    }
    return ;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", num + i);
    heap_sort(num, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    return 0;
}
