/*************************************************************************
	> File Name: 4.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 23时26分02秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string str;
    cin >> str;
    int ans = 1000;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'L') {
            ans --;
        } else {
            ans ++;
        }
    }
    switch(ans % 4) {
        case 0: cout << "N" << endl;break;
        case 1: cout << "E" << endl;break;
        case 2: cout << "S" << endl;break;
        case 3: cout << "W" << endl;break;
    }
    return 0;
}
