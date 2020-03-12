/*************************************************************************
	> File Name: b.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年02月06日 星期四 13时45分28秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v;
    while(n--) {
        char input;
        cin >> input;
        v.push_back(input - '0');
    }
    int one = 0, six = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) one++;
        if (v[i] == 6) six++;
    }
    if (one >= six) cout << six - 1 << endl;
    else cout << one << endl;
    return 0;
}
