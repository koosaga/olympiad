/*
第一个扫描线，纪念一下
n条线，m个点，求每个点所在区域的面积
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
struct point{double x,y;int to,t1,t2;}up[1000],down[1000],pp[400000];
struct line{double a,b,c;}li[1000];
int n,m,i,j,len,x,y,q,h,mid,tx[1000],to[1000];
double l,S[1000],ans[120000];
vector <int> ve[1000];

bool Cmp_Line(line a,line b)
{
	 double X,Y;
	 if (abs(a.b)<1e-9)	X=1000000000000000000000000.0;else	X=-a.a/a.b;
	 if (abs(b.b)<1e-9)	Y=1000000000000000000000000.0;else	Y=-b.a/b.b;
	 if (abs(X-Y)>1e-9)	return X<Y;
	 if (X!=1000000000000000000000000.0)	return -a.c/a.b>-b.c/b.b;
	 else	return -a.c/a.a<-b.c/b.a;
}

bool Cmp_Point(point a,point b)
{
	if (abs(a.x-b.x)>1e-9)	return a.x<b.x;
	if (abs(a.y-b.y)>1e-9)	return a.y<b.y;
	if (a.t1!=b.t1)	return a.t1<b.t1;
	return a.t2<b.t2;
}
double cp(point a,point b)
{
	return a.x*b.y-a.y*b.x;
}
double f(int k,double x)
{
	if (abs(li[k].b)>1e-9)	return (-li[k].c-li[k].a*x)/li[k].b;
	if (x<-li[k].c/li[k].a)	return -1000000000000000000000000.0;
	else	return 1000000000000000000000000.0;
}
int main()
{
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	scanf("%d%d%lf",&n,&m,&l);
	for (i=1;i<=n;i++)	scanf("%lf%lf%lf",&li[i].a,&li[i].b,&li[i].c);
	li[n+1].a=1;li[n+1].b=0;li[n+1].c=l;
	li[n+2].a=1;li[n+2].b=0;li[n+2].c=-l;
	li[n+3].a=0;li[n+3].b=1;li[n+3].c=l;
	li[n+4].a=0;li[n+4].b=1;li[n+4].c=-l;
	n+=4;
	for (i=1;i<=m;i++)
	{
		scanf("%lf%lf",&pp[i].x,&pp[i].y);
		pp[i].to=i;
	}
	len=m;
	sort(li+1,li+n+1,Cmp_Line);
	for (i=1;i<=n;i++)
		for (j=1;j<i;j++)
		if (abs(li[j].b*li[i].a-li[i].b*li[j].a)>1e-9)
		{
			len++;
			pp[len].y=(li[i].c*li[j].a-li[j].c*li[i].a)/(li[j].b*li[i].a-li[i].b*li[j].a);
			pp[len].x=(li[i].c*li[j].b-li[j].c*li[i].b)/(li[j].a*li[i].b-li[i].a*li[j].b);
			pp[len].t1=j;
			pp[len].t2=i;
		}
	sort(pp+1,pp+len+1,Cmp_Point);
	for (i=1;i<=n;i++)	tx[to[i]=i]=i;
	for (i=1;i<=len;i++)
	{
		if (pp[i].to)
		{
			q=0;h=n;
			while (q<h-1)
			{
				mid=(q+h)/2;
				if (f(tx[mid],pp[i].x)<pp[i].y)	h=mid;
				else	q=mid;
			}
			ve[h].push_back(i);
		}
		else
		{
			x=pp[i].t1;y=pp[i].t2;
			x=to[x];y=to[y];
			if (x>y)	swap(x,y);
			
			//终结y这块
			S[y]+=cp(pp[i],up[y])+cp(down[y],pp[i]);
			for (j=0;j<int(ve[y].size());j++)	ans[pp[ve[y][j]].to]=S[y]/2;
			S[y]=0;
			up[y]=down[y]=pp[i];
			ve[y].clear();
			//...
			
			swap(tx[x],tx[y]);to[tx[x]]=x;to[tx[y]]=y;
			//上面那块
			S[x]+=cp(down[x],pp[i]);down[x]=pp[i];
			//下面那块
			S[y+1]+=cp(pp[i],up[y+1]);up[y+1]=pp[i];
		}
	}
	for (i=1;i<=m;i++)	printf("%.2lf\n",ans[i]);
}