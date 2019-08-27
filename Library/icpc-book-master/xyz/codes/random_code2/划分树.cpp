#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,i,m,q,h,k,len,t1,t2,p,T[2],to[200001],a[200001],l[1000000],r[1000000],qian[1000000],hou[1000000],s[5000000],next[2][5000000];
 
bool cmp(int x,int y)
{
    return a[x]<a[y];
}
 
void mkt(int k,int q,int h)
{
    l[k]=q;r[k]=h;
    if (q==h)
    {
        len+=2;
        qian[k]=len-1;hou[k]=len;
        s[len]=n+1;s[len-1]=to[q];
    }
    else
    {
        mkt(k*2,q,(q+h)/2);
        mkt(k*2+1,(q+h)/2+1,h);
        T[0]=hou[k*2];T[1]=hou[k*2+1];
        qian[k]=len+1;hou[k]=len+h-q+2;
        for (s[hou[k]]=n+1,next[0][hou[k]]=T[0],next[1][hou[k]]=T[1],t1=hou[k*2]-1,t2=hou[k*2+1]-1,p=hou[k]-1;p>=qian[k];p--)
        {
            if (t2<qian[k*2+1]||(t1>=qian[k*2]&&s[t1]>s[t2]))
                s[p]=s[T[0]=t1--];
            else    s[p]=s[T[1]=t2--];
            next[0][p]=T[0];next[1][p]=T[1];
        }
        len=hou[k];
    }
}
 
int fi(int k,int t1,int t2,int kk)
{
    if (l[k]==r[k]) return a[to[l[k]]];
    else    if (next[0][t2]-next[0][t1]>=kk) return fi(k*2,next[0][t1],next[0][t2],kk);
    else    return fi(k*2+1,next[1][t1],next[1][t2],kk-next[0][t2]+next[0][t1]);
}
 
int main()
{
    scanf("%d",&n);
    for (i=1;i<=n;i++)   scanf("%d",&a[i]);
    for (i=1;i<=n;i++)   to[i]=i;
    sort(to+1,to+n+1,cmp);
    mkt(1,1,n);
    scanf("%d",&m);
    while (m--)
    {
        scanf("%d%d%d",&q,&h,&k);
        q++;h++;
        printf("%d\n",fi(1,qian[1]+q-1,qian[1]+h,k));
    }
}
