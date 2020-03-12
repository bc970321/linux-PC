/*************************************************************************
	> File Name: 4.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月21日 星期一 19时41分16秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

map<int, int> m;

int myhash(string &str) {
    int k = 0;
    cout << str;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] > '0' && str[i] < '9')
        k = k * 10 + str[i] - '0';
    }
    return k;
}

int main() {
    string str1, str2, str3;
    //char str1[100], str2[100],str3[100];
    double n = 0;
    FILE *fp = fopen("./input4", "r");

    while(fscanf(fp, "%s%s%s", str1, str2, str3) != EOF) {
        cout << str2 << endl;
        int value = myhash(str2);
        m[value]++;
        n++;
    }
    double ans = 0;
    map<int,int>::iterator it;

    for (it = m.begin(); it != m.end(); it++) {
        cout << it->first << " " << it->second << endl;
        ans += (it->second / n) * log(it->second / n);
    }
    
    ans *= -1;
    
    cout << ans << endl;
    fclose(fp);
    return 0;
}
