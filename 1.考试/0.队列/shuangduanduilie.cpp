/*************************************************************************
	> File Name:    shuangduanduilie.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月09日 星期二 22时23分19秒
 ************************************************************************/
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<queue>
#include<set>
#include<map>
using namespace std;
 
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
void print(int x)
{if(x<0)x=-x,putchar('-');if(x>=10)print(x/10);putchar(x%10+'0');}
 
const int N=200100;
 
struct Node{int x,pos;}a[N];
 
int n,cnt,ans;
int Max[N],Min[N];
 
bool cmp(const Node &A,const Node &B)
{
    if(A.x!=B.x) return A.x<B.x;
    return A.pos<B.pos;
}
 
int main()
{
    n=read();
	for(int i=1;i<=n;i++)
    a[i].x=read(),a[i].pos=i;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
	if(a[i].x!=a[i-1].x||i==1)
	{
		Max[cnt]=a[i-1].pos;
		Min[++cnt]=a[i].pos;
	}
    Max[cnt]=a[n].pos;
    int h=0X3f3f3f3f;
	bool b=true;
    for(int i=1;i<=cnt;i++)
	if(!b)
	{
		if(h>Max[i]) h=Min[i];
		else h=Max[i],b=true;
	}
	else
	{
		if(h<Min[i]) h=Max[i];
		else ans++,h=Min[i],b=false;
	}
    printf("%d\n",ans);
    return 0;
}
