/*************************************************************************
	> File Name:    tt.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 18时36分16秒
 ************************************************************************/

#include<stdio.h>

int main() {
    for (int i = 2; i < 100; i++) {
        int falg = 0;
        for (int j = 2; j < i / 2; j++) {
            if (i % j == 0) falg = 1;
        }
        if (!falg) printf("%d\n", i);
    }
    return 0;
}
