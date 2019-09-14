/*************************************************************************
	> File Name:    huandongchuangkou.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月09日 星期二 22时35分34秒
 ************************************************************************/
#include<cstdio>
#include<algorithm>
#include<cstring>
#define LL long long
#define rg register
#define N 1000010
#define ls (u<<1)
#define rs (u<<1|1)
#define mid ((a[u].l+a[u].r)>>1) 
using namespace std;
int n,m;
struct tree{
    int l,r,mx,mn;
}a[N<<2];
inline int read(){
    int k=0,f=1; char c=getchar();
    while(c<'0'||c>'9')c=='-'&&(f=-1),c=getchar();
    while('0'<=c&&c<='9')k=k*10+c-'0',c=getchar();
    return k*f;
}
void build(int u,int l,int r){
    a[u].l=l; a[u].r=r;
    if(l<r){
        build(ls,l,mid),build(rs,mid+1,r);
        a[u].mx=max(a[ls].mx,a[rs].mx);
        a[u].mn=min(a[ls].mn,a[rs].mn);
    }
    else a[u].mx=a[u].mn=read(); 
}
int query(int u,int l,int r,int type){
    if(l<=a[u].l&&a[u].r<=r) return type?a[u].mx:a[u].mn;
    if(type){
        int ret=-1e9;
        if(l<=mid) ret=max(ret,query(ls,l,r,type));
        if(r>mid) ret=max(ret,query(rs,l,r,type));
        return ret;
    }
    else{
        int ret=1e9;
        if(l<=mid) ret=min(ret,query(ls,l,r,type));
        if(r>mid) ret=min(ret,query(rs,l,r,type));
        return ret;
    }
}
int main(){
    n=read(); m=read(); build(1,1,n);
    for(rg int i=1;i<=n-m+1;i++) printf("%d ",query(1,i,i+m-1,0));//min
    puts("");
    for(rg int i=1;i<=n-m+1;i++) printf("%d ",query(1,i,i+m-1,1));//max
    printf("\n");
    return 0;
}
