//////////////////////////
//
// SPOJ Baby Steps Giant Steps
//
//////////////////////////
#include<ext/hash_map>
using namespace __gnu_cxx;
typedef long long ll;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
void gce(int a,int b,int&x,int&y) {
  if(!b){x=1,y=0;return;}
  gce(b,a%b,x,y);
  int t=x;x=y,y=t-a/b*x;
}
int inv(int a,int b,int c) {
  int x,y;
  gce(a,c,x,y),x=(ll)x*b%c;
  return x<0?x+c:x;
}
int pov(int a,int b,int c) {
  ll r=1%c,t=a%c;
  for(;b;t=t*t%c,b/=2)
    if(b&1)r=r*t%c;
  return r;
}
hash_map<int,int> x;
inline int ask(int a){if(x.find(a)!=x.end())return x[a];else return -1;}
inline int add(int a,int b){if(x.find(a)==x.end())x[a]=b;}
int ff(int a,int b,int c) {
  int t,d=1%c,p=0;
  for(int i=0,k=1%c;i<=50;k=(ll)k*a%c,i++) if(k==b)return i;
  while((t=gcd(a,c))!=1) {
    if(b%t)return -1;
    p++,c/=t,b/=t,d=(ll)d*a/t%c;
  }
  int m=ceil(sqrt(double(c)));
  x.clear();
  for(int i=0,k=1%c;i<m;add(k,i),k=(ll)k*a%c,i++);
  for(int i=0,f=pov(a,m,c);i<m;d=(ll)d*f%c,i++)
    if((t=ask(inv(d,b,c)))!=-1)return i*m+t+p;
  return -1;
}
int main() {
  int a,b,c,t;
  while(scanf("%d%d%d",&a,&c,&b),a)
    if((t=ff(a,b,c))==-1)puts("No Solution");else printf("%d\n",t);
  return 0;
}