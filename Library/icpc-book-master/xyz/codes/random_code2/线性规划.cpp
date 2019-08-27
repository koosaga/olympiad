/*
	线性规划单纯形
	算法详见算法导论 这里不再叙述
	题目是xjoi球的移动那题 但因为那题数据大 所以会T 精度也不够
	但用来跑正常一点的图 还是蛮可靠的 而且是万能的
	其实那题用不着讨论有些情况 但因为是模版 我还是写了
	有以下几个注意点
	1：-x0的最大值如果取不到0 那么就是impossible
	2：在做完辅助线性规划后 x0可能不是基本变量 所以还要消一次
	3：如果存在xi在最优值中的系数为正 且任何约束都无法制约他 那么就是 No boundary
	4：结果注意四舍五入
	5：注意某些恶心的精度问题
	6：最后的答案就是z[0][0]
	7：实际测评后float比double快不了多少 但是long double 就坑爹了
*/

#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int n,i,j,len,lenx,k,a[1001],zhu[2100];
double z[2100][4100];														// 7
bool can;

void xiao(int lenx,int x,int y)
{
	if (z[y][zhu[x]]==0)	return ;
	for (int i=0;i<=lenx;i++)
	if (i!=zhu[x])	z[y][i]+=z[y][zhu[x]]*z[x][i];
	z[y][zhu[x]]=0;
}

void ti(int len,int lenx,int x,int y)
{
	int i;
	z[x][zhu[x]]=-1;
	zhu[x]=y;
	for (i=0;i<=lenx;i++)
	if (i!=y)	z[x][i]/=-z[x][y];
	z[x][y]=0;
	for (i=0;i<=len;i++)	if (i!=x)	xiao(lenx,x,i);
}

bool avoid(int len,int lenx)
{
	int i,k,kk;
	for (k=0,i=lenx;i;i--)	if (z[0][i]>0)	k=i;
	if (!k)	return false;
	for (kk=0,i=1;i<=len;i++)
	if (z[i][k]<0&&(!kk||(z[i][0]/z[i][k]>z[kk][0]/z[kk][k])))	kk=i;
	if (!kk)																// 3
	{
		can=false;
		return true;
	}
	ti(len,lenx,kk,k);
	return true;
}

int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)	scanf("%d",&a[i]);
	for (i=1;i<=n;i++)
	{
		zhu[i]=i+n*2;
		z[i][i==1?n:i-1]=1;
		z[i][i]=-1;
		z[i][i==n?n+1:i+n+1]=1;
		z[i][i+n]=-1;
		z[i][0]=a[i];
	}
	for (i=n+1;i<=2*n;i++)
	{
		zhu[i]=i+n*2;
		z[i][i==1+n?n:i-n-1]=-1;
		z[i][i-n]=1;
		z[i][i==2*n?n+1:i+1]=-1;
		z[i][i]=1;
		z[i][0]=1-a[i-n];
	}
	len=2*n;
	lenx=n*4;
	for (z[0][lenx+1]=-1,i=1;i<=len;i++)	z[i][lenx+1]=1;
	for (can=true,i=1;i<=len;i++)
	if (z[i][0]<z[k][0])	k=i;
	if (z[k][0]<0)
	{
		ti(len,lenx+1,k,lenx+1);
		while (avoid(len,lenx+1));
		if (abs(z[0][0])>0.00000001)	can=false;							// 1 5 6
	}
	if (!can)
	{
		printf("Impossible\n");												// 1
		return 0;
	}
	for (i=1;i<=len;i++)
	if (zhu[i]==lenx+1)
	{
		for (j=1;j<=lenx;j++)
		if (z[i][j]!=0)	break;
		ti(len,lenx+1,i,j);											// 2
	}
	for (i=0;i<=lenx;i++)	z[0][i]=0;
	for (i=1;i<=2*n;i++)	z[0][i]=-1;
	for (i=1;i<=len;i++)	xiao(lenx,i,0);
	while (avoid(len,lenx))
	if (!can)
	{
		printf("No boundary\n");									// 3
		return 0;
	}
	printf("%d\n",int(-z[0][0]+0.5));								// 4 6
}
