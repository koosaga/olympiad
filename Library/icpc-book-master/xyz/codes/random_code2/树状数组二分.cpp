#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long int64;

int n,k,i,limit,lim2,ma,h[110000];
int64 s,ans,tmp,p,a[1100000],b[1100000];

void modify(int64 *a,int x,int64 t)
{
	if (!x)	return ;
	for (x;x<=limit;x+=x&-x)	a[x]+=t;
}

int64 get(int64 *a,int x)
{
	int64 sum=0;
	for (;x;x-=x&-x)	sum+=a[x];
	return sum;
}

int64 getit()
{
	int x=0,y=(k+1)/2,i;
	for (i=lim2;i>=0;i--)
	{
		x+=(1<<i);
		if (a[x]>=y)	x-=(1<<i);
		else	y-=a[x];
	}
	return x+1;
}

int main()
{
	ans=1000000000000000000LL;
	scanf("%d%d",&n,&k);
	for (i=1;i<=n;i++)	scanf("%d",&h[i]),h[i]++,ma=max(ma,h[i]);
	for (limit=1,lim2=0;limit<ma;lim2++,limit*=2);
	for (i=0;i<k;i++)	modify(a,h[i],1),modify(b,h[i],h[i]);
	for (i=k;i<=n;i++)
	{
		modify(a,h[i-k],-1);
		modify(b,h[i-k],-h[i-k]);
		modify(a,h[i],1);
		modify(b,h[i],h[i]);
		p=getit();
		s=get(a,p);
		tmp=(p*s-get(b,p))+(get(b,limit)-get(b,p)-p*(1LL*k-s));
		ans=min(ans,tmp);
	}
	printf("%lld\n",ans);
}