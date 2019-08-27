#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
#define INF 600000000
#define abs(x) ((x)>0?(x):-(x))
int n,m,i,j,x,y,p,ans,a,b,len,till[30001],next[60000],go[60000],fa[30001],pf[30001],l[30001],r[30001],dp[30001][2][2],z[30001][2][2],zuo[30001][2],you[30001][2];
bool rr[30001];
char k;

void add(int x,int y)
{
	next[++len]=till[x];
	till[x]=len;
	go[len]=y;
}

void dfs(int k,int f)
{
	pf[k]=f;
	for (int i=till[k];i;i=next[i])	if (go[i]!=f)	dfs(go[i],k);
}

void downdata(int x)
{
	if (rr[x])
	{
		swap(l[x],r[x]);
		swap(dp[x][0][1],dp[x][1][0]);
		swap(zuo[x],you[x]);
		rr[l[x]]=!rr[l[x]];
		rr[r[x]]=!rr[r[x]];
		rr[x]=false;
	}
}

void updata(int x)
{
	int i,j,p,q;
	downdata(x);downdata(l[x]);downdata(r[x]);
	for (i=0;i<=1;i++)
	for (zuo[x][i]=zuo[l[x]][i],j=0;j<=1;j++)
	for (p=0;p<=1;p++)
	zuo[x][i]=max(zuo[x][i],dp[l[x]][i][j]+z[x][j][p]+max(0,zuo[r[x]][p]));
	for (i=0;i<=1;i++)
	for (you[x][i]=you[r[x]][i],j=0;j<=1;j++)
	for (p=0;p<=1;p++)
	you[x][i]=max(you[x][i],max(0,you[l[x]][p])+z[x][p][j]+dp[r[x]][j][i]);
	for (i=0;i<=1;i++)
	for (j=0;j<=1;j++)
	for (dp[x][i][j]=-INF,p=0;p<=1;p++)
	for (q=0;q<=1;q++)	dp[x][i][j]=max(dp[x][i][j],dp[l[x]][i][p]+z[x][p][q]+dp[r[x]][q][j]);
}

void New(int x)
{
	int i,j;
	char k[2];
	for (i=0;i<=1;i++)	for (k[i]=getchar();k[i]<=32;k[i]=getchar());
	for (i=0;i<=1;i++)
	for (j=0;j<=1;j++)
	if (k[i]=='.'&&k[j]=='.')	z[x][i][j]=abs(i-j)+1;
	else	z[x][i][j]=-INF;
	updata(x);
}

void tr(int x)
{
	int y=fa[x],z=fa[y];
	if (z)
	{
		if (l[z]==y)	l[z]=x;
		else	r[z]=x;
		fa[x]=z;
	}
	else	fa[x]=0,pf[x]=pf[y];
	l[y]=r[x];
	fa[r[x]]=y;
	r[x]=y;
	fa[y]=x;
	updata(y);
}

void tl(int x)
{
	int y=fa[x],z=fa[y];
	if (z)
	{
		if (l[z]==y)	l[z]=x;
		else	r[z]=x;
		fa[x]=z;
	}
	else	fa[x]=0,pf[x]=pf[y];
	r[y]=l[x];
	fa[l[x]]=y;
	l[x]=y;
	fa[y]=x;
	updata(y);
}

void xiao(int x)
{
	if (fa[x])	xiao(fa[x]);
	downdata(x);
}

void splay(int x)
{
	xiao(x);
	int y,z;
	while (fa[x])
	{
		y=fa[x],z=fa[y];
		if (z)
		{
			if (l[z]==y&&l[y]==x||r[z]==y&&r[y]==x)
			{
				if (l[z]==y)	tr(y),tr(x);
				else	tl(y),tl(x);
			}
			else
			{
				if (l[y]==x)	tr(x);
				else	tl(x);
				if (l[z]==x)	tr(x);
				else	tl(x);
			}
		}
		else	if (l[y]==x)	tr(x);
		else	tl(x);
	}
	updata(x);
}

void access(int x)
{
	splay(x);
	pf[r[x]]=x;
	fa[r[x]]=0;
	r[x]=0;
	updata(x);
	while (pf[x])
	{
		splay(pf[x]);
		pf[r[pf[x]]]=pf[x];
		fa[r[pf[x]]]=0;
		r[pf[x]]=x;
		fa[x]=pf[x];
		splay(x);
	}
	rr[x]=true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dp[0][0][0]=dp[0][1][1]=0;
	dp[0][0][1]=dp[0][1][0]=-INF;
	dfs(1,0);
	for (i=1;i<=n;i++)	New(i);
	while (m--)
	{
		for (k=getchar();k<=32;k=getchar());
		if (k=='Q')
		{
			scanf("%d%d",&a,&b);
			access(b);
			access(a);
			downdata(a);
			updata(a);
			ans=max(zuo[a][0],zuo[a][1]);
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d",&p);
			access(p);
			downdata(p);
			New(p);
		}
	}
}
