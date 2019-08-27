///////////////////////////
//
// KD Tree & nearest neighbor
//
///////////////////////////
struct point{int x[5];}p[60000],f[250000],mi[250000],ma[250000],ans[12],b;
int n,k,i,j,t,m,cmp_d,dis[12],d[250000];
bool cmp(point x,point y){return x.x[cmp_d]<y.x[cmp_d];}
void update(int a,int b)
{for (int i=0;i<k;i++)ma[a].x[i]=max(ma[a].x[i],ma[b].x[i]),mi[a].x[i]=min(mi[a].x[i],mi[b].x[i]);}
void build(int t,int q,int h)
{
  int mid=(q+h)/2;
  double mm=-1;
  for (int i=0;i<k;i++)
  {
    double sum=0,ave=0;
    for (int j=q;j<=h;j++)  ave+=p[j].x[i];
    ave/=h-q+1;
    for (int j=q;j<=h;j++)  sum+=sqr(p[j].x[i]-ave);
    if (sum>mm)  mm=sum,d[t]=i;
  }
  cmp_d=d[t];nth_element(p+q,p+mid,p+h+1,cmp);
  mi[t]=ma[t]=f[t]=p[mid];
  if (q<mid)  build(2*t,q,mid-1),update(t,t*2);
  if (mid<h)  build(2*t+1,mid+1,h),update(t,t*2+1);
}
int dist(point a,point b)
{
  int sum=0;
  for (int i=0;i<k;i++)  sum+=sqr(a.x[i]-b.x[i]);
  return sum;
}
int dist(point a,point b,point c)
{
  int sum=0;
  for (int i=0;i<k;i++)
  if (a.x[i]<b.x[i])  sum+=sqr(a.x[i]-b.x[i]);
  else  if (a.x[i]>c.x[i])  sum+=sqr(a.x[i]-c.x[i]);
  return sum;
}
void test(point a,point b)
{
  int i,j,tmp=dist(a,b);
  for (i=0;i<m;i++)
  if (tmp<dis[i])  break;
  for (j=m-1;j>i;j--)  ans[j]=ans[j-1],dis[j]=dis[j-1];
  ans[i]=a;dis[i]=tmp;
}
void ask(int t,int q,int h,point b)
{
  if (q>h)  return ;
  test(f[t],b);
  if (q==h||dist(b,mi[t],ma[t])>dis[m-1])  return ;
  int mid=(q+h)/2;
  if (b.x[d[t]]<=f[t].x[d[t]])  ask(t*2,q,mid-1,b),ask(t*2+1,mid+1,h,b);
  else  ask(t*2+1,mid+1,h,b),ask(t*2,q,mid-1,b);
}
int main() {
  for (i=1;i<=n;i++)
  for (j=0;j<k;j++)  scanf("%d",&p[i].x[j]);
  build(1,1,n);
}
