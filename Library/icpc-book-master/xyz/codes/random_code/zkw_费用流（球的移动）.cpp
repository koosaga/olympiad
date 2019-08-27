#include<cstdio>
#include<memory.h>
#include<algorithm>
using namespace std;
#define INF 1000000000

int n,i,s,t,x,ans,len,f[10000],fei[10000],next[10000],go[10000],till[1100],ff[1100],mi[1100];
bool o[1100],v[1100],can[1100];

void add(int a,int b,int c,int d)
{
	next[++len]=till[a];
	till[a]=len;
	go[len]=b;
	f[len]=c;
	fei[len]=d;
}

void Ad(int a,int b,int c,int d)
{
	add(a,b,c,d);
	add(b,a,0,-d);
}

bool bfs()
{
	int i,d=INF;
	for (i=s;i<=t;i++)	if (!v[i]&&ff[i]<d)	d=ff[i];
	for (i=s;i<=t;i++)	if (!v[i])	mi[i]+=d;
	memset(v,false,sizeof(v));
	memset(can,true,sizeof(can));
	for (i=s;i<=t;i++)	ff[i]=INF;
	return (d!=INF);
}

int dfs(int k,int mm)
{
	if (k==t)	return mm;
	int i,tmp,sum=0;
	o[k]=true;v[k]=true;
	for (i=till[k];i;i=next[i])
	if (f[i])//只要这样就判吧。相当于有边的话
	{
		ff[go[i]]=min(ff[go[i]],mi[k]+fei[i]-mi[go[i]]);
		if (!o[go[i]]&&can[go[i]]&&mi[k]+fei[i]==mi[go[i]])
		{
			tmp=dfs(go[i],min(mm,f[i]));
			sum+=tmp;
			mm-=tmp;
			f[i]-=tmp;
			f[i&1?i+1:i-1]+=tmp;
			ans+=tmp*fei[i];
			o[k]=false;
			if (!mm)	return sum;
		}
	}
	o[k]=false;
	if (!sum)	can[k]=false;
	return sum;
}

int max_min_flow()
{
	while (bfs())	dfs(s,INF);
	return ans;
}

int main()
{
	scanf("%d",&n);
	s=0;t=n+1;
	for (i=1;i<=n;i++)	scanf("%d",&x),Ad(s,i,x,0);
	for (i=1;i<=n;i++)	Ad(i,t,1,0);
	for (i=1;i<=n;i++)	Ad(i,i==n?1:i+1,INF,1);
	for (i=1;i<=n;i++)	Ad(i,i==1?n:i-1,INF,1);
	printf("%d\n",max_min_flow());
}