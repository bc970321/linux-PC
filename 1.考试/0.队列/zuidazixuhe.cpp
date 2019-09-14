/*************************************************************************
	> File Name:    zuidazixuhe.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月09日 星期二 22时25分50秒
 ************************************************************************/

#include<list>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
 
using namespace std;
 
LL sum[1000010];
 
list<int> q;
 
int main(void)
{
    int n,m,i,j;
    while(scanf("%d%d",&n,&m)==2)
    {
        sum[0] = 0;
        for(i=1;i<=n;i++)
        {
            scanf("%lld",&sum[i]);
            sum[i] += sum[i-1];
        }
        LL maxn = 0;
        while(!q.empty())
            q.pop_back();
        q.push_front(0);
        for(i=1;i<=n;i++)
        {
            while(!q.empty() && sum[q.front()] > sum[i])
            {
                q.pop_front();
            }
            q.push_front(i);
            while(!q.empty() && i - q.back() > m)//如果长度已经超过m
            {
                q.pop_back();
            }
            maxn = max(maxn,sum[i] - sum[q.back()]);
        }
        cout << maxn << endl;
    }
 
    return 0;
}


