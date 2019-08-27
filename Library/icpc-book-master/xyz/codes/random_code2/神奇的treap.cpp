#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
struct T{int sum,z,key,change,lt,rt,ss,ans;bool c,rr;T *l,*r;}f[600001],*f1=f,*null,*root,*q,*trash[4000001];
struct pp{T *l,*r;}*p;
int n,m,trashlen,c,tot,post,xx[600001];
char S[20];
inline void read(int &x)
{
    char k;
    bool fu=false;
    for (k=getchar();k<=32;k=getchar());
    if (k=='-') fu=true,k=getchar();
    for (x=0;'0'<=k;k=getchar()) x=x*10+k-'0';
    if (fu) x*=-1;
}
inline void downdate(T *k)
{
    if (k==null)    return ;
    if (k->c)
    {
        k->z=k->change;
        k->ss=k->z*k->sum;
        k->rt=k->lt=max(0,k->z)*k->sum;
        k->ans=max(k->z,k->z*k->sum);
        k->l->c=k->r->c=true;
        k->l->change=k->r->change=k->change;
        k->c=false;
    }
    if (k->rr)
    {
        swap(k->l,k->r);
        swap(k->lt,k->rt);
        k->l->rr=!k->l->rr;
        k->r->rr=!k->r->rr;
        k->rr=false;
    }
}
inline void update(T *k)
{
    downdate(k->l);downdate(k->r);
    k->sum=k->l->sum+k->r->sum+1;
    k->ss=k->l->ss+k->r->ss+k->z;
    k->lt=max(k->l->lt,k->l->ss+k->z+k->r->lt);
    k->rt=max(k->r->rt,k->r->ss+k->z+k->l->rt);
    k->ans=max(max(k->l->ans,k->r->ans),k->l->rt+k->z+k->r->lt);
}
inline void split(T *k,int x)
{
    if (k==null)    p->l=p->r=null;
    else
    {
        downdate(k);
        if (k->l->sum+1<=x)    split(k->r,x-k->l->sum-1),k->r=p->l,p->l=k,update(k);
        else    split(k->l,x),k->l=p->r,p->r=k,update(k);
    }
}
inline T *merge(T *x,T *y)
{
    if (x==null)    return y;else   if (y==null)    return x;
    if (x->key>y->key)
    {
        downdate(x);
        x->r=merge(x->r,y);
        update(x);
        return x;
    }
    else
    {
        downdate(y);
        y->l=merge(x,y->l);
        update(y);
        return y;
    }
}
inline void dfs_make(T *&k,int q,int h)
{
    if (trashlen)   k=trash[trashlen--];
    else    k=++f1;
    int ma=q;
    for (int i=q+1;i<=h;i++) if (xx[i]>xx[ma])    ma=i;
    if (q<ma)    dfs_make(k->l,q,ma-1);else   k->l=null;
    read(k->z);
    k->key=xx[ma];k->rr=k->c=false;
    if (ma<h)    dfs_make(k->r,ma+1,h);else   k->r=null;
    update(k);
}
inline void make_it(T *&k,int n)
{
    for (int i=1;i<=n;i++)   xx[i]=rand();
    dfs_make(k,1,n);
}
inline void goto_trash(T *k)
{
    trash[++trashlen]=k;
    if (k->l!=null)  goto_trash(k->l);
    if (k->r!=null)  goto_trash(k->r);
}
int main()
{
    null=new T;null->l=null->r=null;null->sum=null->ss=null->lt=null->rt=0;null->ans=-1000000000;
    p=new pp;
    read(n);read(m);
    make_it(root,n);
    while (m--)
    {
        scanf("%s",S);
        if (S[0]=='I'){
            read(post);read(n);
            make_it(q,n);
            split(root,post);
            root=merge(p->l,q);
            root=merge(root,p->r);
        }else   if (S[0]=='D')
        {
            read(post);read(tot);
            split(root,post-1);
            root=p->l;
            split(p->r,tot);
            goto_trash(p->l);
            root=merge(root,p->r);
        }else   if (S[0]=='R')
        {
            read(post);read(tot);
            split(root,post-1);
            root=p->l;
            split(p->r,tot);
            p->l->rr=!p->l->rr;
            root=merge(root,p->l);
            root=merge(root,p->r);
        }else   if (S[0]=='G')
        {
            read(post);read(tot);
            split(root,post-1);
            root=p->l;
            split(p->r,tot);
            downdate(p->l);
            printf("%d\n",p->l->ss);
            root=merge(root,p->l);
            root=merge(root,p->r);
        }else   if (S[2]=='K')
        {
            read(post);read(tot);read(c);
            split(root,post-1);
            root=p->l;
            split(p->r,tot);
            p->l->c=true;
            p->l->change=c;
            root=merge(root,p->l);
            root=merge(root,p->r);
        }else   printf("%d\n",root->ans);
    }
}