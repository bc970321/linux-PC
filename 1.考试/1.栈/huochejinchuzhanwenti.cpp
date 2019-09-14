/*************************************************************************
	> File Name:    huochejinchuzhanwenti.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月10日 星期三 10时03分43秒
 ************************************************************************/
#include <cstdio>
#include <cmath>

using namespace std;

const int max=6002;
int n,l,ss;
unsigned long long a[max];
int bz[120005],z[120005],b[120005];

unsigned long long ksm(int a,int b){
    int g=b;
    unsigned long long x=1,c=a;
    while (g){
        if (g&1) x=x*c;
        c*=c;
        g>>=1;
    }
    return x;
}

int solve(int v,int l){
    int z=0,cc=l;
    while (l<=v){
        z+=v/l;
        l*=cc;
    }
    return z;
}

int main(){
    scanf("%d",&n);
    if (n==1){printf("1");return 0;}    

    for (int i=2;i<=2*n;i++)
        if (!bz[i]){
            int k=2;
            z[++ss]=i;
            while (k*i<=2*n){
                bz[k*i]=1;
                k++;
            }
        }

    for (int i=1;i<=ss;i++)
        b[z[i]]-=solve(n-1,z[i]);
    for (int i=1;i<=ss;i++)
        b[z[i]]-=solve(n+1,z[i]);
    for (int i=1;i<=ss;i++)
        b[z[i]]+=solve(2*n-1,z[i]);
    b[2]++;     

    a[max-1]=1;l=max-1;
    for (int i=1;i<=ss;i++)
    if (b[z[i]]){
        unsigned long long k=ksm(z[i],b[z[i]]);
        unsigned long long x=0;
        for (int j=max-1;j>=l;j--){
            a[j]=a[j]*k+x;
            x=a[j]/100000000;
            a[j]%=100000000;
        }
        while (x){
            l--;
            a[l]=x%100000000;
            x/=100000000;
        }
    }
    printf("%d",a[l]);
    for (int i=l+1;i<=max-1;i++){
        if (a[i]<1) {printf("00000000");continue;}
        if (a[i]<10) {printf("0000000%d",a[i]);continue;}
        if (a[i]<100) {printf("000000%d",a[i]);continue;}
        if (a[i]<1000) {printf("00000%d",a[i]);continue;}
        if (a[i]<10000) {printf("0000%d",a[i]);continue;}
        if (a[i]<100000) {printf("000%d",a[i]);continue;}
        if (a[i]<1000000) {printf("00%d",a[i]);continue;}
        if (a[i]<10000000) {printf("0%d",a[i]);continue;}
        printf("%d",a[i]);
    }
    printf("\n");
    return 0;
}

