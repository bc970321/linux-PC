/*************************************************************************
	> File Name:    kuohaohuajia.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月10日 星期三 10时31分16秒
 ************************************************************************/

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxl=100010;
 
char c[maxl];int len;
char sta[maxl];int top=0;
int f[maxl];//记录f[i]层的括号数 
 
int main()
{
    scanf("%s",c+1);
    len=strlen(c+1);
    int ans=0;
    for(int i=1;i<=len;i++)
    {
        if(c[i]=='(' || c[i]=='[' || c[i]=='{')
        {
            sta[++top]=c[i];
        }
        else if(top!=0)
        {
            if(c[i]==sta[top]+1 || c[i]==sta[top]+2)
            {
                f[top]+=2;
                f[top-1]+=f[top];
                f[top]=0;
                top--;
            }
            else
            {
                while(1)
            {
                ans=max(ans,f[top]);
                f[top]=0;
                if(top==0) break;
                top--;
                }
            }
        }
    }
    while(1) {
        ans=max(ans,f[top]);
        f[top]=0;
        if(top==0) break;
        top--;
    }
    printf("%d\n",ans);
    return 0;
}

