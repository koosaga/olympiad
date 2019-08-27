#include <cstdio>
using namespace std;
#define N 110000
#define A 48271LL
#define mo 2147483647
struct node{int z,key,sum;node *l,*r;}f[N],*f1=f,*root,*null;
struct aa{node *l,*r;}*p;
int m,Min,len,delta,x,ans,X;
char k;
inline int ra(){X=A*X%mo;return X;}
inline void update(node *x){;x->sum=x->l->sum+x->r->sum+1;}
node *merge(node *x,node *y)
{
	if (x==null)	return y;else	if (y==null)	return x;
	if (x->key<y->key)
	{
		x->r=merge(x->r,y);
		update(x);
		return x;
	}
	else
	{
		y->l=merge(x,y->l);
		update(y);
		return y;
	}
}
void split(node *x,int k)
{
	if (x==null)	p->l=p->r=null;
	else
	{
		if (x->z<k)	split(x->r,k),x->r=p->l,p->l=x;
		else	split(x->l,k),x->l=p->r,p->r=x;
		update(x);
	}
}
void insert(int x)
{
	f1++;
	f1->sum=1;
	f1->z=x;
	f1->key=ra();
	f1->l=f1->r=null;
	split(root,x);
	root=merge(p->l,f1);
	root=merge(root,p->r);
}
int get(int x)
{
	node *p=root;
	while (p!=null)
	{
		if (x<=p->l->sum)	p=p->l;
		else	if (p->l->sum+1==x)	return p->z+delta;
		else	x-=p->l->sum+1,p=p->r;
	}
	return -1;
}
int main()
{
	scanf("%d%d",&m,&Min);
	null=new node;
	p=new aa;
	null->l=null->r=null;
	null->sum=null->z=0;
	X=1;root=null;
	while (m--)
	{
		for (k=getchar();k<=32;k=getchar());
		scanf("%d",&x);
		if (k=='I')
		{
			if (x>=Min)	insert(x-delta);
		}
		else	if (k=='A')	delta+=x;
		else	if (k=='F')	printf("%d\n",get(root->sum-x+1));
		else
		{
			delta-=x;
			split(root,Min-delta);
			root=p->r;
			ans+=p->l->sum;
		}
	}
	printf("%d\n",ans);
}