#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 100000
int T,l,i,ans,height[N],wa[N],wb[N],wv[N],s[N],rank[N],sa[N];
char S[N];
bool cmp(int a,int b,int l,int *x)	{return x[a]==x[b]&&x[a+l]==x[b+l];}
void da(char *r,int n,int m,int *sa)
{
	int *x=wa,*y=wb,i,j,p;
	for (i=0;i<m;i++)	s[i]=0;
	for (i=0;i<n;i++)	s[x[i]=r[i]]++;
	for (i=1;i<m;i++)	s[i]+=s[i-1];
	for (i=0;i<n;i++)	sa[--s[x[i]]]=i;
	for (j=p=1;p<n;m=p,j*=2)
	{
		for (p=0,i=n-j;i<n;i++)	y[p++]=i;
		for (i=0;i<n;i++)	if (sa[i]>=j)	y[p++]=sa[i]-j;
		for (i=0;i<n;i++)	wv[i]=x[y[i]];
		for (i=0;i<m;i++)	s[i]=0;
		for (i=0;i<n;i++)	s[wv[i]]++;
		for (i=1;i<m;i++)	s[i]+=s[i-1];
		for (i=n-1;i>=0;i--)	sa[--s[wv[i]]]=y[i];
		for (swap(x,y),x[sa[0]]=0,p=1,i=1;i<n;i++)
		x[sa[i]]=cmp(sa[i-1],sa[i],j,y)?p-1:p++;
	}
}
void calheight(char *r,int n,int *sa,int *height)
{
	int i,j,k=0;
	for (i=1;i<=n;i++)	rank[sa[i]]=i;
	for (i=0;i<n;height[rank[i++]]=k)
	for (k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%s",S);
		l=strlen(S);
		da(S,l+1,255,sa);
		calheight(S,l,sa,height);
		for (ans=0,i=1;i<=l;i++)	ans+=l-sa[i]-height[i];
		printf("%d\n",ans);
	}
}