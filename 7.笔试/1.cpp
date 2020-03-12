/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月22日 星期日 19时44分40秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
    int n;
    cin >> n;
    while(n--)  {
        string a;
        cin >> a;
        if (a.size() < 3) {
            cout << a << endl;
            continue;
        }
        char t1 = a[0], t2 = a[1];
        cout << t1 << t2;
        for (int i = 2; i < a.size(); i++) {
            if (t1 == t2 && t2 == a[i]) {
                continue;
            }
            if (i != a.size() - 1 && t1 == t2 && a[i] == a[i + 1]) {
                continue;
            }
            t1 = t2;
            t2 = a[i];
            cout << a[i];
            if (i == a.size() - 1) cout << endl;
        }
    }
    return 0;
}
