/*************************************************************************
	> File Name:    feituyouxi.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月10日 星期三 11时01分34秒
 ************************************************************************/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<utility>
#include<iostream>
using namespace std;
int n,m;
 
const int MAXN=1000+5;
 
int s[MAXN][MAXN]= {{0}};
 
struct node
{
    int kuan,gao;
} st[MAXN];
int tp,sz;
 
inline void read(int &x)
{
    x=0;
    register short k=1;
    register char t=getchar();
    while(t>'9'||t<'0')
    {
        if(t=='-')k=-k;
        t=getchar();
    }
    while(t>='0'&&t<='9')
    {
        x*=10;
        x+=(t-'0');
        t=getchar();
    }
    x*=k;
}
 
int main()
{
    read(n);
    read(m);
    char tmp;
    for(register int i=1; i<=n; ++i)
    {
        for(register int j=1; j<=m; ++j)
        {
            tmp=getchar();
            while(tmp!='F'&&tmp!='R')tmp=getchar();
            if(tmp=='F')
            {
                s[i][j]=s[i-1][j]+1;
            }
        }
    }
    int ans=0;
    for(int i=1; i<=n; ++i)
    {
        int maxs=0;
        st[1].gao=s[i][1];
        st[1].kuan=1;
        tp=1;
        for(int j=2;j<=m;++j){
            int tmp=0;
            while(st[tp].gao>=s[i][j]&&tp){
                tmp+=st[tp].kuan;
                maxs=max(maxs,st[tp].gao*tmp);
                --tp;
            }
            ++tp;
            st[tp].gao=s[i][j];
            st[tp].kuan=tmp+1;
        }
        int tmp=0;
        while(tp){
            tmp+=st[tp].kuan;
            maxs=max(maxs,st[tp].gao*tmp);
            --tp;
        }
        ans=max(ans,maxs);
    }
    printf("%d\n",3*ans);
    return 0;
}

