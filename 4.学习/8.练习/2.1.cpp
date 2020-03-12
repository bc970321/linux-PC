/*************************************************************************
	> File Name: 2.1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年03月07日 星期六 23时11分41秒
 ************************************************************************/
#include<iostream>
using namespace std;
 
int main(){
    int left, right;
    int result = 0;      
    cin >> left >> right;
    for(int i=left; i<=right; ++i){
        switch(i%3){
            case 1: ;break;
            case 2: ++result;break;
            case 0: ++result;break;
        }
    }
        cout << result << endl;
}
