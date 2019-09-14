/*************************************************************************
	> File Name:    G.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月11日 星期四 17时46分33秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 100005;

struct Elem
{
	int height;
	int count;
};

Elem stack[N];
int top;

int main()
{
	int height, n;
	long long ans, t, tmp;
	while (scanf("%d", &n) != EOF && n)
	{
		top = 0;
		ans = 0;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &height);
			tmp = 0;
			while (top > 0 && stack[top - 1].height >= height)
			{
				t = stack[top - 1].height * (stack[top - 1].count + tmp);
				if (t > ans) ans = t;
				tmp += stack[top - 1].count;
				--top;
			}
			stack[top].height = height;
			stack[top].count = 1 + tmp;
			++top;
		}
		tmp = 0;
		while (top > 0)
		{
			t = stack[top - 1].height * (stack[top - 1].count + tmp);
			if (t > ans) ans = t;
			tmp += stack[top - 1].count;
			--top;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

