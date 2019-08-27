#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char S[300000];
int k,ans,i,l,next[300000];

int main()
{
	while (scanf("%s",S+1)!=-1)
	{
		l=strlen(S+1);
		for (i=l;i;i--)	S[i*2]=S[i];
		for (i=1;i<=l+1;i++)	S[i*2-1]='*';
		for (next[k=ans=1]=0,i=2;i<=2*l;i++)
		{
			if (k+next[k]>=i)	next[i]=min(next[2*k-i],k+next[k]-i);
			else	next[i]=0;
			while (i+next[i]<=2*l&&i-next[i]>1&&S[i+next[i]+1]==S[i-next[i]-1])	next[i]++;
			if (i+next[i]>k+next[k])	k=i;
			ans=max(ans,next[i]);
		}
		printf("%d\n",ans);
	}
}