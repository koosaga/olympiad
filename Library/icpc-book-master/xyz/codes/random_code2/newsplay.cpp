#include <cstdio>
#include <algorithm>
using namespace std;

struct T{int sum,z,hao;T *son[2],*fa;}f[110000],*f1=f,*root[110000],*null;
int n,m,q,a,b,i,ff[110000];
char k;
void update(T *x){x->sum=x->son[0]->sum+x->son[1]->sum+1;}
void rotate(T *x,bool t)
{
	T *y=x->fa,*z=y->fa;
	y->son[t]=x->son[!t];
	x->son[!t]->fa=y;
	x->son[!t]=y;
	y->fa=x;
	x->fa=z;
	if (z!=null)	z->son[z->son[1]==y]=x;
	update(y);
}
void splay(T *x,T *&root)
{
	T *y,*z;
	while (x!=root&&x->fa!=null)
	{
		y=x->fa;z=y->fa;
		bool t1=(x==y->son[1]),t2=(y==z->son[1]);
		if (y==root)	rotate(x,t1);
		else	if (t1^t2)	rotate(x,t1),rotate(x,t2);
		else	rotate(y,t2),rotate(x,t2);
	}
	root=x;
	update(x);
}
void insert(T *&k,T *x,T *fa,T *&root)
{
	if (k==null)
	{
		k=x;
		k->son[0]=null;
		k->son[1]=null;
		k->fa=fa;
		k->sum=1;
		splay(k,root);
	}
	else	if (x->z<k->z)	insert(k->son[0],x,k,root);
	else	insert(k->son[1],x,k,root);
}
int get(T *&x,int k)
{
	T *p=x;
	if (k>x->sum)	return -1;
	while (true)
	{
		if (k<=p->son[0]->sum)	p=p->son[0];
		else	if (k==p->son[0]->sum+1)	break;
		else	k-=p->son[0]->sum+1,p=p->son[1];
	}
	splay(p,x);
	return p->hao;
}
void dfs_ins(T *&root,T *k)
{
	if (k==null)	return ;
	dfs_ins(root,k->son[0]);
	dfs_ins(root,k->son[1]);
	insert(root,k,null,root);
}
void bing(int x,int y)
{
	if (x==y)	return ;
	if (root[x]->sum<root[y]->sum)	swap(x,y);
	dfs_ins(root[x],root[y]);
	ff[y]=x;
}
int gf(int k)
{
	if (ff[k]!=k)	ff[k]=gf(ff[k]);
	return ff[k];
}
int main()
{
	null=new T;null->son[0]=null->son[1]=null->fa=null;null->sum=0;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++)
	{
		root[i]=++f1;root[i]->son[0]=root[i]->son[1]=root[i]->fa=null;root[i]->sum=1;root[i]->hao=i;
		scanf("%d",&root[i]->z);
		ff[i]=i;
	}
	while (m--)
	{
		scanf("%d%d",&a,&b);
		bing(gf(a),gf(b));
	}
	scanf("%d",&m);
	while (m--)
	{
		for (k=getchar();k<=32;k=getchar());
		scanf("%d%d",&a,&b);
		if (k=='B')	bing(gf(a),gf(b));
		else	printf("%d\n",get(root[gf(a)],b));
	}
}