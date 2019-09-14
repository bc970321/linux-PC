/*************************************************************************
	> File Name:    pengyouduilie.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月09日 星期二 22时42分30秒
 ************************************************************************/
#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

int main()
{
    int T=1;
    int n; 
    while(cin>>n&&n!=0)
    {
        map<int,int> group; 
        for(int i=0;i<n;i++)
        {
            int m;
            cin>>m;
            for(int j=0;j<m;j++)
            {
                int name;  
                cin>>name;
                group[name] = i; 
            }
        }

        string str;
        queue<int> que;
        queue<int> per[1003];

        //cout<<"Scenario #"<< T++ <<endl;
        while(cin>>str&&str!="STOP")
        {
            if(str == "ENQUEUE")
            {
                int name; 
                cin>>name;
                int qn=group[name];
                if(per[qn].empty())  
                    que.push(qn); 
                per[qn].push(name);
            }
            else
            {
                int qn=que.front(); 
                cout<<per[qn].front()<<endl; 
                per[qn].pop();  
                if(per[qn].empty())
                    que.pop();
            }
        }
        cout<<endl;
    }
}
