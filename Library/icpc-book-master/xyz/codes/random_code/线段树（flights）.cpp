/*orz lich*/
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long double ld;
int n,i,j,L,R,m,limit,len,len2,p[51000],x[51000],y[51000],l[200000],r[200000],
	qian[200000],hou[200000],qian2[200000],hou2[200000],ma[1300000][19],xx[1500000],ll[1500000],rr[1500000],to[1500000];
ld a[51000],b[51000],c[51000];

void join(int k,int p,int l,int r)
{
	// if (k==2)	printf("%d %d\n",l,r);
	if (l>r)	return ;
	len2++;
	ll[len2]=l;
	rr[len2]=r;
	to[len2]=p;
	if (qian2[k]<len2&&to[len2]==to[len2-1])	len2--,rr[len2]=rr[len2+1];
}

void mkt(int k,int q,int h)
{
	l[k]=q;r[k]=h;
	if (q<h)
	{
		int q1,q2,L,R;
		mkt(k*2,q,(q+h)/2);
		mkt(k*2+1,(q+h)/2+1,h);
		qian[k]=len+1;q1=qian[k*2];q2=qian[k*2+1];
		while (q1<=hou[k*2]||q2<=hou[k*2+1])
		{
			if (q2>hou[k*2+1]||q1<=hou[k*2]&&xx[q1]<xx[q2])	xx[++len]=xx[q1],ma[len][0]=ma[q1][0],q1++;
			else	if (q2<=hou[k*2+1]&&xx[q2]<xx[q1]||q1>hou[k*2])	xx[++len]=xx[q2],ma[len][0]=ma[q2][0],q2++;
			else	xx[++len]=xx[q1],ma[len][0]=max(ma[q1][0],ma[q2][0]),q1++,q2++;
		}
		hou[k]=len;
		q1=qian2[k*2];q2=qian2[k*2+1];L=0;
		qian2[k]=len2+1;
		while (q1<=hou2[k*2]||q2<=hou2[k*2+1])
		{
			while (q1<=hou2[k*2]&&rr[q1]<L)	q1++;
			while (q2<=hou2[k*2+1]&&rr[q2]<L)	q2++;
			if (q2>hou2[k*2+1]&&q1>hou2[k*2])	break;
			if (q2>hou2[k*2+1])	L=max(L,ll[q1]),join(k,to[q1],L,rr[q1]),L=rr[q1]+1;
			else	if (q1>hou2[k*2]) L=max(L,ll[q2]),join(k,to[q2],L,rr[q2]),L=rr[q2]+1;
			else
			{
				L=max(L,min(ll[q1],ll[q2]));
				R=min(rr[q1],rr[q2]);
				if (ll[q1]>L)	R=min(R,ll[q1]-1);
				if (ll[q2]>L)	R=min(R,ll[q2]-1);
				if (R<ll[q2])	join(k,to[q1],L,R),L=rr[q1]+1;
				else	if (R<ll[q1])	join(k,to[q2],L,R),L=rr[q2]+1;
				else
				{
					ld A=a[to[q1]]-a[to[q2]],B=b[to[q1]]-b[to[q2]],C=c[to[q1]]-c[to[q2]],xx,xx1,delta;
					int x1=to[q1],x2=to[q2];
					if (abs(A)<1e-13)
					{
						if (abs(B)<1e-13)
						{
							if (C>0)	join(k,x1,L,R);
							else	join(k,x2,L,R);
						}
						else
						{
							if (B<0)	swap(x1,x2),A=-A,B=-B,C=-C;
							xx=-C/B;
							if (xx<=L-1e-13)	join(k,x1,L,R);
							else	if (xx>=R-1e-13)	join(k,x2,L,R);
							else	join(k,x2,L,int(xx+1e-13)),join(k,x1,int(xx+1e-13)+1,R);
						}
					}
					else
					{
						if (A<0)	swap(x1,x2),A=-A,B=-B,C=-C;
						delta=B*B-4*A*C;
						if (delta<=1e-13)	join(k,x1,L,R);
						else
						{
							xx=(-B-sqrt(delta))/(2.0*A);
							xx1=(-B+sqrt(delta))/(2.0*A);
							if (xx<=L-1e-13)
							{
								if (xx1<=L-1e-13)	join(k,x1,L,R);
								else	if (xx1<R-1e-13)	join(k,x2,L,int(xx1+1e-13)),join(k,x1,int(xx1+1e-13)+1,R);
								else	join(k,x2,L,R);
							}
							else	if (xx<=R-1e-13)
							{
								if (xx1<=R-1e-13)	join(k,x1,L,int(xx+1e-13)),join(k,x2,int(xx+1e-13)+1,int(xx1+1e-13)),join(k,x1,int(xx1+1e-13)+1,R);
								else	join(k,x1,L,int(xx+1e-13)),join(k,x2,int(xx+1e-13)+1,R);
							}
							else	join(k,x1,L,R);
						}
					}
				}
				L=R+1;
			}
		}
		hou2[k]=len2;
	}
	else
	{
		qian[k]=hou[k]=++len;
		xx[len]=x[q];ma[len][0]=y[q];
		qian2[k]=hou2[k]=++len2;
		ll[len2]=max(0,p[q]);rr[len2]=min(50000,2*x[q]-p[q]);to[len2]=q;
	}
}

ld gg(int k,int X,int Y)
{
	ld Max=0;
	int q,h,i,mid;
	if (ll[qian2[k]]<=X)
	{
		for (q=qian2[k],h=hou2[k]+1;q<h-1;)
		{
			mid=(q+h)/2;
			if (ll[mid]<=X)	q=mid;
			else	h=mid;
		}
		Max=max(Max,a[to[q]]*X*X+b[to[q]]*X+c[to[q]]);
	}
	if (ll[qian2[k]]<=Y)
	{
		for (q=qian2[k],h=hou2[k]+1;q<h-1;)
		{
			mid=(q+h)/2;
			if (ll[mid]<=Y)	q=mid;
			else	h=mid;
		}
		Max=max(Max,a[to[q]]*Y*Y+b[to[q]]*Y+c[to[q]]);
	}
	if (xx[qian[k]]<=Y)
	{
		q=qian[k];
		for (i=limit;i>=0;i--)	if (q+(1<<i)<=hou[k]&&xx[q+(1<<i)]<X)	q=q+(1<<i);
		if (xx[q]<X-1e-9)	q++;
		for (i=limit;i>=0;i--)	if (q+(1<<i)-1<=hou[k]&&xx[q+(1<<i)-1]<=Y)	Max=max(Max,ld(ma[q][i])),q=q+(1<<i);
	}
	return Max;
}

ld get(int k,int q,int h,int xx,int yy)
{
	if (l[k]==q&&r[k]==h)	return gg(k,xx,yy);
	if (h<=r[k*2])	return get(k*2,q,h,xx,yy);
	if (q>=l[k*2+1])	return get(k*2+1,q,h,xx,yy);
	return max(get(k*2,q,r[k*2],xx,yy),get(k*2+1,l[k*2+1],h,xx,yy));
}

int main()
{
	// freopen("lich.in","r",stdin);
	// freopen("lich.out","w",stdout);
	scanf("%d",&n);
	for (i=1;i<=n;i++)	scanf("%d%d%d",&p[i],&x[i],&y[i]);
	for (i=1;i<=n;i++)	a[i]=ld(-y[i]+0.0)/ld(p[i]-x[i])/ld(p[i]-x[i]),b[i]=ld(-2.0)*x[i]*a[i],c[i]=ld(1)*a[i]*x[i]*x[i]+y[i];
	//for (i=1;i<=n;i++)	printf("%lf %lf %lf\n",a[i],b[i],c[i]);
	mkt(1,1,n);
	limit=min(18,int(log(len)/log(2)));
	//printf("%d\n",limit);
	for (i=1;i<=limit;i++)
	for (j=1;j+(1<<(i-1))<=len;j++)	ma[j][i]=max(ma[j][i-1],ma[j+(1<<(i-1))][i-1]);
	//for (i=qian2[2];i<=hou2[2];i++)	printf("%d %d %d\n",ll[i],rr[i],to[i]);
	scanf("%d",&m);
	while (m--)
	{
		scanf("%d%d%d%d",&i,&j,&L,&R);
		printf("%.8lf\n",double(get(1,i,j,L,R)));
	}
}
