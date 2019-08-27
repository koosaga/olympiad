#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n,i,init,L,len,ll,q,h,ch,p,last[1700000],n1[1700000],du[1700000],s[1700000],fa[800001],l[1700000],son[1700000][3],parent[1700000];
char S[8000001],k;
long long ans,sum[1600001];
void read(int &x)
{
        char k;
        for (k=getchar();k<=32;k=getchar());
        for (x=0;'0'<=k;k=getchar())    x=x*10+k-'0';
}
void ins(int p,int ss,int k)
{
	int np=++len,q,nq;
	l[np]=l[p]+1;
	s[np]=1;
	while (p&&!son[p][k])   son[p][k]=np,p=parent[p];
	if (!p) parent[np]=1;
	else {
		q=son[p][k];
		if (l[p]+1==l[q])       parent[np]=q;
		else {
			nq=++len;
			l[nq]=l[p]+1;
			s[nq]=0;
			son[nq][0]=son[q][0];
			son[nq][1]=son[q][1];
			son[nq][2]=son[q][2];
			parent[nq]=parent[q];
			parent[q]=nq;
			parent[np]=nq;
			while (p&&son[p][k]==q) son[p][k]=nq,p=parent[p];
		}
	}
	last[ss]=np;
}
int main()
{
        freopen("string.in","r",stdin);
        freopen("string.out","w",stdout);
        read(n);
        last[1]=init=len=1;
        for (i=2;i<=n;i++)
        {
                read(fa[i]);
                for (k=getchar();k<=32;k=getchar());
                ins(last[fa[i]],i,k-'a');
        }
        for (i=1;i<=len;i++)    du[parent[i]]++;
        for (i=1;i<=len;i++)    if (!du[i])     n1[++h]=i;
        for (q=1;q<=h;q++)
        {
                s[parent[n1[q]]]+=s[n1[q]];
                du[parent[n1[q]]]--;
                if (!du[parent[n1[q]]]) n1[++h]=parent[n1[q]];
        }
        for (i=len+1;i;i--)     sum[n1[i]]=sum[parent[n1[i]]]+s[n1[i]]*(l[n1[i]]-l[parent[n1[i]]]);
        for (p=1,len=0,scanf("%s",S),L=strlen(S),i=0;i<L;i++)
        {
                ch=S[i]-'a';
                for (;p>1&&!son[p][ch];p=parent[p],len=l[p]);
                if (!son[p][ch])        p=1,len=0;
                else    p=son[p][ch],len++,ans+=sum[parent[p]]+s[p]*len-s[p]*l[parent[p]];
        }
        cout<<ans<<endl;
}
