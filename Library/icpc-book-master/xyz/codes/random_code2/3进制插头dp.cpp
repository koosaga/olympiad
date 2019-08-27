/*
	三进制括号匹配
	hash+滚动数组
	有障碍哈密尔顿回路个数
*/

#include<iostream>
#include<cstdio>
using namespace std;

int n,m,i,j,p,x,q,len,lenq,li,lj,zhan[20],to[20],s[20],a[15][15],m3[20],tt[1600000];
long long sx,dui[2][250000],duiq[2][250000];
char k;

int T(int k)//伪hash
{
	if (!tt[k])
	{
		tt[k]=++len;
		dui[0][len]=k;
	}
	return tt[k];
}

int main()
{
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++)
	{
		for (k=getchar();k<=32;k=getchar());
		a[i][j]=(k=='.');
	}
	lenq=1;duiq[0][1]=0;duiq[1][1]=1;
	for (m3[0]=1,i=1;i<=13;i++)	m3[i]=m3[i-1]*3;
	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++)
	if (a[i][j])	li=i,lj=j;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			for (len=0,p=1;p<=lenq;p++)
			{
				for (x=duiq[0][p],q=0;q<=m;q++,x/=3)	s[q]=x%3;
				for (zhan[0]=0,q=0;q<=m;q++)
				if (s[q]==1)	zhan[++zhan[0]]=q;
				else	if (s[q]==2)	to[zhan[zhan[0]]]=q,to[q]=zhan[zhan[0]],zhan[0]--;
				if (a[i][j])
				{
					if (!s[j-1]&&!s[j])	dui[1][T(duiq[0][p]+m3[j-1]+2*m3[j])]+=duiq[1][p];
					if (!s[j-1]&&s[j])	dui[1][T(duiq[0][p])]+=duiq[1][p],dui[1][T(duiq[0][p]-s[j]*m3[j]+s[j]*m3[j-1])]+=duiq[1][p];
					if (s[j-1]&&!s[j])	dui[1][T(duiq[0][p])]+=duiq[1][p],dui[1][T(duiq[0][p]-s[j-1]*m3[j-1]+s[j-1]*m3[j])]+=duiq[1][p];
					if (s[j-1]&&s[j])
					{
						if (s[j-1]==1&&s[j]==1)	dui[1][T(duiq[0][p]-m3[j-1]-m3[j]-m3[to[j]])]+=duiq[1][p];
						if (s[j-1]==1&&s[j]==2&&(i==li&&j==lj))	dui[1][T(duiq[0][p]-m3[j-1]-2*m3[j])]+=duiq[1][p];//合并同一个联通快只有在最后一个元素才行
						if (s[j-1]==2&&s[j]==1)	dui[1][T(duiq[0][p]-2*m3[j-1]-m3[j])]+=duiq[1][p];
						if (s[j-1]==2&&s[j]==2)	dui[1][T(duiq[0][p]-2*m3[j-1]-2*m3[j]+m3[to[j-1]])]+=duiq[1][p];
					}
				}
				else
				if (!s[j-1]&&!s[j])	dui[1][T(duiq[0][p])]+=duiq[1][p];
			}
			lenq=len;
			for (sx=0,p=1;p<=len;p++)
			{
				duiq[0][p]=dui[0][p];
				tt[dui[0][p]]=0;
				if (!dui[0][p])	sx=dui[1][p];
				duiq[1][p]=dui[1][p];
				dui[1][p]=0;
			}
			if (i==li&&j==lj)
			{
				cout<<sx<<endl;
				return 0;
			}
		}
		for (len=0,j=1;j<=lenq;j++)
		if (duiq[0][j]<m3[m])	duiq[0][++len]=duiq[0][j]*3,duiq[1][len]=duiq[1][j];//换行
		lenq=len;
	}
}
