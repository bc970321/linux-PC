/*************************************************************************
	> File Name:    gongsiderenwu.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 11时02分51秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
int main ()
{
    typedef struct T_L
    {
        int time;
        int rank;
        bool is_sure;
    }T_L;
    class mygreator_t  //时间比较仿函数
    {
    public:
        bool operator()(T_L left,T_L right)
        {
            return (left.time > right.time);
        }
    };
    class mygreator_r    //等级比较仿函数
    {
    public:
        bool operator()(T_L left, T_L right)
        {
            return (left.rank > right.rank);
        }
    };
    int n= 0, m = 0;
    scanf("%d%d", &n, &m);   //输入机器数量和任务数量
    vector<T_L> machine(n);
    vector<T_L> task(m);
    for (int i = 0; i < n; i++)  //机器
    {
        scanf("%d %d",&machine[i].time,&machine[i].rank);
    }
    for (int i = 0; i < m; i++)  //任务
    {
        scanf("%d %d", &task[i].time, &task[i].rank);
    }
    sort(machine.begin(), machine.end(), mygreator_r());
    sort(task.begin(), task.end(), mygreator_r());
    sort(machine.begin(), machine.end(), mygreator_t());
    sort(task.begin(), task.end(), mygreator_t());
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (machine[i].time>=task[j].time&&machine[i].rank>=task[j].rank&&task[j].is_sure == false&&machine[i].is_sure==false)
            {

                machine[i].is_sure = true;
                task[j].is_sure = true;
                break;
            }
        }
    }
    int result = 0;
    int count = 0;
    for (int k = 0; k < m; k++)
    {
        if (task[k].is_sure)
        {
            count++;
            result += (500 * task[k].time + 2 * task[k].rank);
        }
    }
    printf("%d %d\n", count,result);
}

