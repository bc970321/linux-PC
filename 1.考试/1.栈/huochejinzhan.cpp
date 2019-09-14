/*************************************************************************
	> File Name:    huochejinzhan.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月10日 星期三 10时16分57秒
 ************************************************************************/

#include <stdio.h>
int n, d;
int stack[22], top = 0, k = 0;
int w = 0;
int a[22];
int sum = 0;
int over = 0;
void dfs(){
	int i, j;
	if(over)
		return;
	d++;
	for(i = 0; i < 2; ++i)
	{
		if(i == 0)
		{
			if(top == 0)
				continue;
			top--;
			a[k++] = stack[top];
			if(d == 2 * n)
			{
				if(sum >= 20)
				{
					over = 1;
					return;
				}
				for(j = 0; j < n; ++j)
				{
					printf("%d", a[j]);
				}
				sum++;
				printf("\n");
			}
			else 
				dfs();
			k--;
			stack[top] = a[k];
			top++;
		}
		else
		{
			w++;
			stack[top++] = w;
			if(w <= n)
				dfs();
			w--;
			top--;
		}
	}
	d--;
}
int main(void){
	scanf("%d", &n);
	dfs();
	return 0;
}

