#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
int n,i,len1,len2,j,p,ans,x[1001],s[1001][1001],lx[1001],ly[1001],li[1001],slack[1001];
bool u[1001],v[1001];

bool fi(int k)
{
	u[k]=true;
	for (int i=1;i<=len2;i++)
	if (!v[i])
	{
		int p=lx[k]+ly[i]-s[k][i];
		if (!p)
		{
			v[i]=true;
			if (!li[i]||fi(li[i]))
			{
				li[i]=k;
				return true;
			}
		}
		else	slack[i]=min(slack[i],p);
	}
	return false;
}
void doit()
{
	int d,i,j;
	for (i=1;i<=len1;i++)
	while (true)
	{
		memset(v,false,sizeof(v));
		for (j=1;j<=i;j++)	u[j]=false;
		for (j=1;j<=len2;j++)	slack[j]=30000;
		if (fi(i))	break;
		for (d=30000,j=1;j<=len2;j++)	if (!v[j])	d=min(d,slack[j]);
		for (j=1;j<=i;j++)	if (u[j])	lx[j]-=d;
		for (j=1;j<=len2;j++)	if (v[j])	ly[j]+=d;
	}
}
int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)	scanf("%d",&x[i]);
	for (i=1;i<=n;i++)
	for (j=2;j<=x[i];j++)
	{
		len1++;
		for (len2=0,p=1;p<=n;p++)
		if (x[p]==0)	len2++,s[len1][len2]=n-min(abs(i-p),n-abs(i-p));
	}
	for (i=1;i<=len1;i++)
	for (lx[i]=-10000,j=1;j<=len2;j++)	lx[i]=max(lx[i],s[i][j]);
	doit();
	for (ans=len1*n,i=1;i<=len2;i++)	ans-=lx[i]+ly[i];
	printf("%d\n",ans);
}
