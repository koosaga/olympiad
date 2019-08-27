////////////////////////
//
// Miller-Rabin + Pollard Rho
//
//////////////////////////
#define P 1000000007
#define M 3010
int B[M],I[M],F[M],IF[M],L,pb[20];ll pa[20];
// a*x + b*y = 1
void gcd(int a,int b,int &x,int &y) {
  if(b==0){x=1,y=0;return;}
  gcd(b,a%b,y,x),y-=a/b*x;
}
int inv(int n) {
  int x,y;gcd(n,P,x,y);
  if(x<0)x+=P;return x;
}
ll mul(ll x,ll y,ll z){return (x*y-(ll)(x/(ld)z*y+1e-3)*z+z)%z;}
ll pow(ll x,ll y,ll z) {
  ll s=1,t=x; for(;y;y/=2,t=mul(t,t,z))if(y&1)s=mul(s,t,z);
  return s;
}
int pow(int x,int y) {
  int s=1,t=x;
  for(;y;y/=2,t=(ll)t*t%P)if(y&1)s=(ll)s*t%P;
  return s;
}
bool chk(ll n,int k) {
  ll s=n-1;int w=0;
  for(;~s&1;s/=2)w++;
  ll y=pow(k,s,n);
  if(y==1||y==n-1)return 1;
  while(w--){y=mul(y,y,n);if(y==n-1)return 1;}
  return 0;
}
bool pr(ll n) {
// checked p <= 1k. if use separately remove first line (may need to check 1)
  if(n<=1000000)return 1;
  return chk(n,2)&&chk(n,3)&&chk(n,5)&&chk(n,7)&&chk(n,11)&&chk(n,13)&&chk(n,17)&&chk(n,19)&&chk(n,23);
}
void add(ll x) {
  for(int i=0;i<L;i++)if(pa[i]==x){pb[i]++;return;}
  pa[L]=x,pb[L++]=1;
}
void rho(ll n) {
  if(n==1)return;
  if(pr(n)){add(n);return;}
  while(1) {
    ll x=2,y=2,z=1;int p=rand()%100000000;
    while(z==1)
      x=(mul(x,x,n)+p)%n,
      y=(mul(y,y,n)+p)%n,
      y=(mul(y,y,n)+p)%n,
      z=__gcd(abs(y-x),n);
    if(z==n)continue;
    rho(z),rho(n/z);return;
  }
}
void fac(ll n){L=0;for(int i=2;i<=1000;i++)while(n%i==0)n/=i,add(i);rho(n);}

F[0]=1;for(int i=1;i<M;i++)F[i]=(ll)F[i-1]*i%P;
IF[M-1]=inv(F[M-1]);for(int i=M-1;i;i--)IF[i-1]=(ll)IF[i]*i%P;
I[1]=1;for(int i=2;i<M;i++)I[i]=(ll)i*(P/i)%P*(P/i)%P*I[P%i]%P*I[P%i]%P;