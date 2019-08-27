#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,i,a,b,m,len,till[50000],go[100000],next[100000],fa[50000],ma[50000],ss[50000],sum[50000],z[50000],F[50000],n1[50000],h[50000];
char S[10];
void add(int a,int b)
{
	next[++len]=till[a];
	till[a]=len;
	go[len]=b;
}
void Bfs()
{
	int q,hh,i,limit=int(sqrt(n));
	for (n1[q=hh=1]=1,F[1]=1,sum[1]=1,ma[1]=z[1],ss[1]=z[1];q<=hh;q++)
	for (i=till[n1[q]];i;i=next[i])
	if (go[i]!=fa[n1[q]])
	{
		int p=go[i];
		n1[++hh]=p;
		fa[p]=n1[q];
		h[p]=h[n1[q]]+1;
		if (sum[F[fa[p]]]+1>limit)
		{
			F[p]=p;
			ma[p]=ss[p]=z[p];
			sum[p]=1;
		}
		else
		{
			F[p]=F[fa[p]];
			ma[p]=max(ma[fa[p]],z[p]);
			ss[p]=ss[fa[p]]+z[p];
			sum[F[p]]++;
		}
	}
}
void modify(int a)
{
	int q,h,i;
	if (F[fa[a]]==F[a])	ma[a]=max(ma[fa[a]],z[a]),ss[a]=ss[fa[a]]+z[a];
	else	ma[a]=ss[a]=z[a];
	for (n1[q=h=1]=a;q<=h;q++)
	for (i=till[n1[q]];i;i=next[i])
	if (go[i]!=fa[n1[q]]&&F[go[i]]==F[n1[q]])
	{
		n1[++h]=go[i];
		ma[go[i]]=max(ma[fa[go[i]]],z[go[i]]);
		ss[go[i]]=ss[fa[go[i]]]+z[go[i]];
	}
}
int get_max(int a,int b)
{
	int Ma=-30000;
	while (F[a]!=F[b])
	{
		if (h[F[a]]>h[F[b]])
		{
			Ma=max(Ma,ma[a]);
			a=fa[F[a]];
		}
		else
		{
			Ma=max(Ma,ma[b]);
			b=fa[F[b]];
		}
	}
	while (h[a]>h[b])	Ma=max(Ma,z[a]),a=fa[a];
	while (h[b]>h[a])	Ma=max(Ma,z[b]),b=fa[b];
	while (a!=b)	Ma=max(Ma,max(z[a],z[b])),a=fa[a],b=fa[b];
	Ma=max(Ma,z[a]);
	return Ma;
}
int get_sum(int a,int b)
{
	int sum=0;
	while (F[a]!=F[b])
	{
		if (h[F[a]]>h[F[b]])
		{
			sum+=ss[a];
			a=fa[F[a]];
		}
		else
		{
			sum+=ss[b];
			b=fa[F[b]];
		}
	}
	while (h[a]>h[b])	sum+=z[a],a=fa[a];
	while (h[b]>h[a])	sum+=z[b],b=fa[b];
	while (a!=b)	sum+=z[a]+z[b],a=fa[a],b=fa[b];
	sum+=z[a];
	return sum;
}
int main()
{
	scanf("%d",&n);
	for (i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for (i=1;i<=n;i++)	scanf("%d",&z[i]);
	Bfs();
	scanf("%d",&m);
	while (m--)
	{
		scanf("%s%d%d",S,&a,&b);
		if (S[1]=='M')	printf("%d\n",get_max(a,b));
		else	if (S[1]=='S')	printf("%d\n",get_sum(a,b));
		else	z[a]=b,modify(a);
	}
}