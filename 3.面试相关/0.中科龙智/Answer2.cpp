/*************************************************************************
	> File Name:    text1.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月07日 星期二 11时27分40秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define MAX_SIZE 128

struct Word {
    int nums;
    char a[MAX_SIZE];
};

bool cmp(struct Word a1, struct Word a2) {
    return a1.nums > a2.nums;
}


int main() {
    struct Word w[3000];
    FILE *fp;
    for (int i = 0; i < 3000; i++) {
        w[i].nums = 1;
    }
    
    char filename[MAX_SIZE];
    printf("Please input the name of the file : \n");
    scanf("%s", filename);
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Error opening!\n");
        exit(0);
    }
    
    int len = 0, j = 0, flag = 0, n;
    while(!feof(fp)) {
        char ch = fgetc(fp);
        w[len].a[j] = '\0';
        if (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122) {
            w[len].a[j] = ch;
            j++;
            flag = 1;
        } else if (ch == ' ' && flag == 1) {
            flag = 0;
            j = 0;
            n = len;
            len ++;
            if (n >= 1) {
                for (int i = 0; i < n; i++) {
                    if (strcmp(w[n].a, w[i].a) == 0) {
                        w[i].nums ++;
                        len -= 1;
                    }
                }
            }
        }
    }
    
    sort(w, w + len, cmp);
    
    printf("The most commonly %d words:\n", len >= 9 ? 10 : len + 1); 
    
    for (int i = 0; i <= (len >= 9 ? 9 : len); i++) {
        printf("%s 的出现次数为 %d\n", w[i].a, w[i].nums);
    }

    return 0;
}
