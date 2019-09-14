/*************************************************************************
	> File Name:    test.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年05月08日 星期三 14时41分37秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1;
    for(int i = 0; i < 100; i++) {
        v1.push_back(i);
    }
    for (int i = 99; i > 0; i--) {
        cout << v1[i] << " ";
    }
    return 0;
}

