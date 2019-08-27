#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,p,i,l,k,ans1,ans2,ans3,ddd,cnt,pp[300000],next[300000];
char S[300000],ss[300000];

int main()
{
	scanf("%d",&T);
	for (p=1;p<=T;p++)
	{
		scanf("%s",S+1);
		l=strlen(S+1);
		for (i=l+1;i<=2*l;i++)	S[i]=S[i-l];
		for (next[1]=0,i=2,k=1;i<=l;i++)
		{
			next[i]=max(0,min(next[i-k+1],k+next[k]-i));
			while (S[i+next[i]]==S[next[i]+1])	next[i]++;
			if (i+next[i]>k+next[k])	k=i;
		}
		next[1]=2*l;
		// for (i=1;i<=l;i++)	ss[i]=S[i];
		// for (i=l+1;i<=2*l;i++)	ss[i]=S[i-l];
		// for (i=1,k=0;i<=2*l;i++)
		// {
		// 	pp[i]=max(0,min(next[i-k+1],k+pp[k]-i));
		// 	while (pp[i]<l&&ss[i+pp[i]]==S[pp[i]+1])	pp[i]++;
		// 	if (i+pp[i]>k+pp[k])	k=i;
		// }
		for (ans1=ans2=ans3=0,i=1;i<=l;i++)
		if (next[i]>=l)	ans2++;
		else	if (S[i+next[i]]<S[next[i]+1])	ans1++;
		else	ans3++;
		for (k=next[1]=0,i=2;i<=l;i++)
		{
			for (;k&&S[k+1]!=S[i];k=next[k]);
			if (S[k+1]=S[i])	k++;
			next[i]=k;
		}
		if (l%(l-next[l])==0)	cnt=l/(l-next[l]);
		else	cnt=1;
		printf("Case %d: %d %d %d\n",p,ans1/cnt,ans2/cnt,ans3/cnt);
	}
}