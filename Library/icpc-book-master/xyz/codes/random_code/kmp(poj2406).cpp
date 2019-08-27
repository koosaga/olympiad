#include<cstdio>
#include<cstring>
using namespace std;

char s[1100000];
int next[1100000],i,q,l;

int main()
{
	while (scanf("%s",s+1),l=strlen(s+1),s[1]!='.'||l>1)
	{
		next[1]=q=0;
		for (i=2;i<=l;i++)
		{
			for (;q&&s[q+1]!=s[i];q=next[q]);
			if (s[q+1]==s[i])	q++;
			next[i]=q;
		}
		if (l%(l-next[l])==0)	printf("%d\n",l/(l-next[l]));
		else	printf("1\n");
	}
}
