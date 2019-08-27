/*
	别忘了添一个空的字符啊啊啊
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int i,l,sa[300000],wa[300000],wv[300000],wb[300000],s[300000];
char S[300000];

bool cmp(int a,int b,int j,int *x)
{
	return x[a]==x[b]&&x[a+j]==x[b+j];
}

void da(char *r,int n,int m)
{
	int *x=wa,*y=wb,i,j,p;
	for (i=0;i<m;i++)	s[i]=0;
	for (i=0;i<n;i++)	s[x[i]=r[i]]++;
	for (i=1;i<m;i++)	s[i]+=s[i-1];
	for (i=0;i<=n;i++)	sa[--s[x[i]]]=i;
	for (j=1,p=1;p<n;m=p,j*=2)
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

int main()
{
	scanf("%s",S);
	for (l=strlen(S),i=0;i<l;i++)	S[l+i]=S[i];
	da(S,2*l+1,256);
	for (i=0;i<=2*l;i++)
	if (sa[i]<l)	printf("%c",S[sa[i]+l-1]);
}
