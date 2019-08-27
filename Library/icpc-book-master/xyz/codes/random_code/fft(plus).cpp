#include<cstdio>
#include<algorithm>
using namespace std;

int n,m,i,j,a[100001],b[100001],lena,lenb;
char q[100010];
long long c[100001];

int main()
{
	freopen("plus.in","r",stdin);
	freopen("plus.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",q+1);
	for (i=1;i<=n;i+=4)
	{
		lena++;
		for (j=min(n,i+3);j>=i;j--)
		a[lena]=a[lena]*10+q[n-j+1]-'0';
	}
	scanf("%s",q+1);
	for (i=1;i<=m;i+=4)
	{
		lenb++;
		for (j=min(m,i+3);j>=i;j--)
		b[lenb]=b[lenb]*10+q[m-j+1]-'0';
	}
	for (i=1;i<=lena;i++)
	for (j=1;j<=lenb;j++)	c[i+j-1]+=a[i]*b[j];
	for (i=1;i<=lena+lenb;i++)	c[i+1]+=c[i]/10000,c[i]%=10000;
	for (i=lena+lenb;!c[i];i--);
	for (printf("%I64d",c[i--]);i;i--)	printf("%04I64d",c[i]);
}
