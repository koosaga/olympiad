/**
 * Author: 
 * Description: Suffix Automaton (SAM)
 */
using namespace std;
int n,i,init,L,len,ll,q,h,ch,p,last[1700000],n1[1700000],du[1700000],s[1700000],fa[800001],l[1700000],son[1700000][3],par[1700000];
char S[8000001],k;
long long ans,sum[1600001];
void ins(int p,int ss,int k)
{
  int np=++len,q,nq;
  l[np]=l[p]+1;
  s[np]=1;
  while (p&&!son[p][k]) son[p][k]=np,p=par[p];
  if (!p) par[np]=1;
  else {
    q=son[p][k];
    if (l[p]+1==l[q]) par[np]=q;
    else {
      nq=++len;
      l[nq]=l[p]+1;
      s[nq]=0;
      memset(son[nq], son[q], sizeof son[q]);
      par[nq]=par[q];
      par[q]=nq;
      par[np]=nq;
      while (p&&son[p][k]==q) son[p][k]=nq,p=par[p];
    }
  }
  last[ss]=np;
}
int main()
{
  read(n);
  last[1]=init=len=1;
  for (i=2;i<=n;i++)
  {
    read(fa[i]);
    for (k=getchar();k<=32;k=getchar());
    ins(last[fa[i]],i,k-'a');
  }
}
