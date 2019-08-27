#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;

int n,i,k,len,x[2000],p[2000],zhan[3030];
double s[1010][3030];

void xiao(int kk,int k)
{
	int i,j;
	s[kk][p[kk]]=-1;
	p[kk]=k;
	for (i=0;i<=3*n+1;i++)	if (i!=k)	s[kk][i]/=-s[kk][k];
	s[kk][k]=0;
	len=0;
	for (i=0;i<=3*n+1;i++)	if (i!=k&&abs(s[kk][i])>1e-9)	zhan[++len]=i;
	for (i=0;i<=n+1;i++)
	if (i!=kk)
	{
		for (j=1;j<=len;j++)	s[i][zhan[j]]+=s[i][k]*s[kk][zhan[j]];
		s[i][k]=0;
	}
}
bool doit(int S)
{
	int i,k,kk;
	for (k=0,i=1;i<=3*n+1;i++)
	if (s[S][i]>0&&(!k||s[S][i]>s[S][k]))	k=i;
	if (!k)	return false;
	for (kk=0,i=1;i<=n;i++)	if (s[i][k]<0&&(!kk||-s[i][0]/s[i][k]<-s[kk][0]/s[kk][k]))	kk=i;
	if (!kk)	return false;
	xiao(kk,k);
	return true;
}
int main()
{
	scanf("%d",&n);
	// for (i=1;i<=n;i++)	scanf("%d",&x[i]);
	x[1]=n;
	for (i=1;i<=n;i++)
	{
		s[i][0]=1-x[i];
		s[i][i]=1;
		s[i][i+n]=1;
		s[i][i==1?n:i-1]=-1;
		s[i][(i==n?1:i+1)+n]=-1;
		p[i]=i+2*n;
		s[i][3*n+1]=1;
	}
	for (i=1;i<=2*n;i++)	s[0][i]=-1;
	s[n+1][3*n+1]=-1;
	for (k=0,i=1;i<=n;i++)	if (!k||s[i][0]<s[k][0])	k=i;
	xiao(k,3*n+1);
	while (doit(n+1));
	for (i=0;i<=n+1;i++)	s[i][3*n+1]=0;
	while (doit(0));
	printf("%d\n",int(-s[0][0]+0.5));
}
