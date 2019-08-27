#include<cstdio>
#include<algorithm>
using namespace std;
int n,i,a,b,m,len,ll,lll,z[40000],deep[40000],F[40000],D[40000],fa[40000],root[40000],zhan[40000],n1[40000],ss[40000],next[80000],go[80000],till[40000],
							ma[200000],sum[200000],l[200000],r[200000];
char S[10];
void add(int a,int b)
{
	next[++lll]=till[a];
	till[a]=lll;
	go[lll]=b;
}
void updata(int k)
{
	ma[k]=max(ma[l[k]],ma[r[k]]);
	sum[k]=sum[l[k]]+sum[r[k]];
}
void mkt(int &k,int q,int h)
{
	k=++ll;
	if (q==h)	ma[k]=sum[k]=z[zhan[q]];
	else
	{
		mkt(l[k],q,(q+h)/2);
		mkt(r[k],(q+h)/2+1,h);
		updata(k);
	}
}
void Bfs()
{
	int q,h,i,j,ma;
	for (n1[q=h=1]=1;q<=h;q++)
		for (i=till[n1[q]];i;i=next[i])
			if (go[i]!=fa[n1[q]])	n1[++h]=go[i],fa[go[i]]=n1[q],deep[n1[h]]=deep[n1[q]]+1;
	for (i=n;i;i--)	ss[n1[i]]++,ss[fa[n1[i]]]+=ss[n1[i]];
	for (i=1;i<=n;i++)
	{
		if (!F[n1[i]])	F[n1[i]]=n1[i];
		for (ma=0,j=till[n1[i]];j;j=next[j])
			if (go[j]!=fa[n1[i]])	if (!ma||ss[go[j]]>ss[ma])	ma=go[j];
		F[ma]=F[n1[i]];
	}
	for (F[0]=0,i=1;i<=n;i++)
	if (ss[i]==1)
	{
		for (len=0,j=i;F[j]==F[i];j=fa[j])	zhan[++len]=j,D[j]=i;
		for (j=1;j*2<=len;j++)	swap(zhan[j],zhan[len-j+1]);
		mkt(root[F[i]],1,len);
	}
}
void modify(int k,int q,int h,int x,int p)
{
	if (q==h)	ma[k]=sum[k]=p;
	else
	{
		if (x<=(q+h)/2)	modify(l[k],q,(q+h)/2,x,p);
		else	modify(r[k],(q+h)/2+1,h,x,p);
		updata(k);
	}
}
int gm(int k,int q,int h,int a,int b)
{
	if (q==a&&h==b)	return ma[k];
	if (b<=(q+h)/2)	return gm(l[k],q,(q+h)/2,a,b);
	if ((q+h)/2<a)	return gm(r[k],(q+h)/2+1,h,a,b);
	return max(gm(l[k],q,(q+h)/2,a,(q+h)/2),gm(r[k],(q+h)/2+1,h,(q+h)/2+1,b));
}
int gs(int k,int q,int h,int a,int b)
{
	if (q==a&&h==b)	return sum[k];
	if (b<=(q+h)/2)	return gs(l[k],q,(q+h)/2,a,b);
	if ((q+h)/2<a)	return gs(r[k],(q+h)/2+1,h,a,b);
	return gs(l[k],q,(q+h)/2,a,(q+h)/2)+gs(r[k],(q+h)/2+1,h,(q+h)/2+1,b);
}
int get_max(int a,int b)
{
	int ma=-30000;
	while (F[a]!=F[b])
	{
		if (deep[F[a]]>deep[F[b]])	ma=max(ma,gm(root[F[a]],deep[F[a]],deep[D[a]],deep[F[a]],deep[a])),a=fa[F[a]];
		else	ma=max(ma,gm(root[F[b]],deep[F[b]],deep[D[b]],deep[F[b]],deep[b])),b=fa[F[b]];
	}
	ma=max(ma,gm(root[F[a]],deep[F[a]],deep[D[a]],min(deep[a],deep[b]),max(deep[a],deep[b])));
	return ma;
}
int get_sum(int a,int b)
{
	int sum=0;
	while (F[a]!=F[b])
	{
		if (deep[F[a]]>deep[F[b]])	sum+=gs(root[F[a]],deep[F[a]],deep[D[a]],deep[F[a]],deep[a]),a=fa[F[a]];
		else	sum+=gs(root[F[b]],deep[F[b]],deep[D[b]],deep[F[b]],deep[b]),b=fa[F[b]];
	}
	sum+=gs(root[F[a]],deep[F[a]],deep[D[a]],min(deep[a],deep[b]),max(deep[a],deep[b]));
	return sum;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for (i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for (i=1;i<=n;i++)	scanf("%d",&z[i]);
	Bfs();
	for (i=1;i<=n;i++)	printf("%d %d\n",F[i],fa[i]);
	scanf("%d",&m);
	while (m--)
	{
		scanf("%s%d%d",S,&a,&b);
		if (S[1]=='M')	printf("%d\n",get_max(a,b));
		else	if (S[1]=='S')	printf("%d\n",get_sum(a,b));
		else	z[a]=b,modify(root[F[a]],deep[F[a]],deep[D[a]],deep[a],z[a]);
	}
}