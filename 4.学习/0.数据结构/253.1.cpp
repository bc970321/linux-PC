/*************************************************************************
	> File Name:    253.1.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 19时44分26秒
 ************************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<set>
#include<bitset>
#include<map>
#include<stack>
#include<queue>
#include<vector>
#include<utility>
#define INF 1000000007
#define inf 100000000000000000
using namespace std;
typedef long long ll;
int c,l,i,j,ans=0;
struct node{
    int mi,ma;
    bool operator<(const node &a)const{
        return ma>a.ma;
    }
}cow[2505],ff;
struct nod{
    int spf,co;
}ss[2505];
bool cmp1(node a,node b)
{
    return a.mi<b.mi;
}
bool cmp2(nod a,nod b)
{
    return a.spf<b.spf;
}
priority_queue<node>que;
int main()
{
    scanf("%d%d",&c,&l);
    for(i=0;i<c;i++)scanf("%d%d",&cow[i].mi,&cow[i].ma);
    for(i=0;i<l;i++)scanf("%d%d",&ss[i].spf,&ss[i].co);
    sort(cow,cow+c,cmp1);
    sort(ss,ss+l,cmp2);
    j=0;
    for(i=0;i<l;i++)
    {
        for(;j<c;j++)
        {
            if(cow[j].mi<=ss[i].spf)que.push(cow[j]);
            else break;
        }
        while(!que.empty()&&ss[i].co)
        {
            ff=que.top();que.pop();
            if(ff.ma>=ss[i].spf)
            {
                ans++;ss[i].co--;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

