/*************************************************************************
	> File Name:    test.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月26日 星期一 16时41分16秒
 ************************************************************************/

#include <iostream>
using namespace std;
const int SIZE = 100;
int matrix[SIZE+1][SIZE+1];
int rowsum[SIZE+1][SIZE+1];
int m,n,i,j,first,last,area,ans;
int main() {
    cin >> m >> n;
    for (i = 1; i <= m; i++) 
        for (j = 1; j <= n; j++)
            cin >> matrix[i][j];
    ans = matrix[1][1];
    for(i = 1; i <= m; i++) {
        rowsum[0][i] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) 
            rowsum[i][j] = rowsum[i][j] + rowsum[i][j - 1];
    }
    for (first = 1; first <= n; first++) {
        for (last = first; last <= n; last++) {
           area = 0;
            for (i = 1; i <= m; i++) {
                area += rowsum[i][last];
                if (area > ans)
                    ans = area;
                if (area < 0)
                    area = 0;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
