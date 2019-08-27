/*
	对这种算法表示仰慕加鄙视
	直接背代码好了= =
*/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct aa{double x,y;}a[110000];
int n,i,j,k;
double xx,yy,rr;

bool out(int k)
{
	return (a[k].x-xx)*(a[k].x-xx)+(a[k].y-yy)*(a[k].y-yy)>rr*rr;
}

void make2(int i,int j)
{
	xx=(a[i].x+a[j].x)/2;
	yy=(a[i].y+a[j].y)/2;
	rr=sqrt((a[j].x-xx)*(a[j].x-xx)+(a[j].y-yy)*(a[j].y-yy));
}

void make3(int i,int j,int k)
{
	double a1,a2,b1,b2,c1,c2;
	a1=(a[i].x-a[j].x)*2;b1=(a[i].y-a[j].y)*2;c1=a[i].x*a[i].x+a[i].y*a[i].y-a[j].x*a[j].x-a[j].y*a[j].y;
	a2=(a[j].x-a[k].x)*2;b2=(a[j].y-a[k].y)*2;c2=a[j].x*a[j].x+a[j].y*a[j].y-a[k].x*a[k].x-a[k].y*a[k].y;
	xx=(c2*b1-c1*b2)/(a2*b1-a1*b2);
	yy=(c2*a1-c1*a2)/(b2*a1-b1*a2);
	rr=sqrt((a[i].x-xx)*(a[i].x-xx)+(a[i].y-yy)*(a[i].y-yy));
}

int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)	scanf("%lf%lf",&a[i].x,&a[i].y);
	random_shuffle(a+1,a+n+1);
	for (make2(1,1),i=2;i<=n;i++)
	if (out(i))	for (make2(i,i),j=1;j<i;j++)
	if (out(j))	for (make2(i,j),k=1;k<j;k++)
	if (out(k))	make3(i,j,k);
	printf("%.2lf %.2lf %.2lf\n",xx,yy,rr);
}
