/*
	2进制插头dp
	有障碍多条回路
*/

#include<iostream>
#include<cstdio>
#include<memory.h>
using namespace std;
int T,I,i,j,p,x,y,n,m,a[15][15];
long long dp[15][15][5000];

int main()
{
	scanf("%d",&T);
	for (I=1;I<=T;I++)
	{
		memset(a,0,sizeof(a));
		memset(dp,0,sizeof(dp));
		scanf("%d%d",&n,&m);
		for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)	scanf("%d",&a[i][j]);
		dp[1][0][0]=1;
		for (i=1;i<=n;i++)
		{
			for (j=1;j<=m;j++)
			for (p=0;p<(1<<m+1);p++)
			{
				x=(p&(1<<j-1));
				y=(p&(1<<j));
				if (a[i][j])
				{
					if (x&&y)
						dp[i][j][p-x-y]+=dp[i][j-1][p];
					else	if (!x&&y)
						dp[i][j][p]+=dp[i][j-1][p],dp[i][j][p-y/2]+=dp[i][j-1][p];
					else	if (x&&!y)
						dp[i][j][p]+=dp[i][j-1][p],dp[i][j][p+x]+=dp[i][j-1][p];
					else	dp[i][j][p+(1<<(j-1))+(1<<j)]+=dp[i][j-1][p];
				}
				else	if (!x&!y)	dp[i][j][p]+=dp[i][j-1][p];
			}
			for (j=0;j<(1<<m);j++)
			dp[i+1][0][(j<<1)]=dp[i][m][j];
		}
		printf("Case %d: There are %I64d ways to eat the trees.\n",I,dp[n][m][0]);
	}
}
