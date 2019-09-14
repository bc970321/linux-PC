/*************************************************************************
	> File Name:    257.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年06月18日 星期二 20时25分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 1010
struct Node{ // 邻接表
	int index; // 节点序号
	struct Node *next; // 指向下一个儿子节点
}node[Max]; 
int num[Max]; //记录节点个数，包括合并后的节点个数
int pre[Max]; //记录节点父节点
int value[Max]; //记录节点权值
bool flag[Max]; //标记是否已经合并
int n,r; // 节点个数、根节点编号
int Sum; // 最少总权值
void add(int a,int b){ //构造邻接表，表中记录着节点a的儿子节点
	struct Node *temp=(struct Node*)malloc(sizeof(struct Node));
	temp->index=b;
	temp->next=node[a].next;
	node[a].next=temp;
}
int find(){ //查找value[i]/num[i]最小值标号，注意不能是根节点
	double tt=-1.0;
	int index;
	for(int i=1;i<=n;i++)
		if(!flag[i] && double(value[i])/num[i]>tt && i!=r){
			tt=double(value[i])/num[i];
			index=i;
		}
	return index;
}
void merge(int pra,int son){ // 合并父节点和子节点，成为新节点，同时更新子节点儿子节点的父亲节点情况
	num[pra]+=num[son]; //合并后的节点数量
	value[pra]+=value[son]; //合并后的节点权值
	struct Node *point=node[son].next;
	while(point!=NULL){ //更新子节点儿子节点父节点情况
		pre[point->index]=pra;
		point=point->next;
	}
}
void cal(){ // 贪心算法求最少总权值
	for(int i=1;i<n;i++){ //需要合并n-1次
		int index=find(); // 查找最大值value[i]/num[i]
		flag[index]=true; //标记已经合并
		int pra=pre[index]; //求其父节点
		while(flag[pra]) //直到没有合并为止
			pra=pre[pra];
		Sum+=(value[index]*num[pra]); //增加合并后的权值
		merge(pra,index);//合并父节点和子节点
	}
	Sum+=value[r]; //最后由于所有除开根节点的节点的权值是实际上是乘以（实际路径-1），故还需要加上所有权值之和以及根节点的权值，而此时value正好为所有节点最初时的权值之和+根节点权值，故这里要加上
}
int main(){
	while(scanf("%d%d",&n,&r),n|r){
		for(int i=1;i<=n;i++){
			scanf("%d",&value[i]); //输入节点权值
			num[i]=1; //初始个数为1
			node[i].next=NULL; // 初始化为NULL，头插法建立邻接表
		}
		int aa,bb;
		memset(flag,0,sizeof(flag)); //初始化为未合并
		for(int i=1;i<n;i++){ //输入边信息
			scanf("%d%d",&aa,&bb);
			add(aa,bb); //建立邻接表
			pre[bb]=aa;
		}
		Sum=0; //初始化为0
		cal(); //贪心计算最下总权值
		printf("%d\n",Sum);//输出
	}
	return 0;
}
