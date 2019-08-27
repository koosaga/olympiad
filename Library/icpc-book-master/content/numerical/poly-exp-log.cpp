/**
 * Author: 
 * Description: polynomial exp/log
 */

// N and n should be powers of 2, N >= 2*n
// Inputs should have size at least 2*n and should be 0-padded
// Non-outputs will not be modified

#define per(i,a,b) for(int i = (b)-1; i >= (a); --i)

const int mo=998244353,g=3;
int qp(int a,int b){
  int ans=1;
  do{if(b&1)ans=1ll*ans*a%mo;a=1ll*a*a%mo;}while(b>>=1);
  return ans;
}
int w[2][N+1];
void dft(int *a,int n,bool v){//0 <= a[i] < mo /// start-hash
  int j=0;
  rep(i,0,n){
    if(i>j)swap(a[i],a[j]);
    for (int p=n>>1;(j^=p)<p;p>>=1);
  }
  for (int i=2;i<=n;i<<=1)
    for (int j=0,s=n/i;j<n;j+=i)
      rep(p,0,i>>1){
        int t=1ll*a[j+p+(i>>1)]*w[v][s*p]%mo;
        a[j+p+(i>>1)]=(a[j+p]+mo-t)%mo;
        a[j+p]=(a[j+p]+t)%mo;
  } if(v){
     int y=qp(n,mo-2);
     rep(i,0,n)a[i]=1ll*a[i]*y%mo;
  }
} /// end-hash

void init(int n){
  int ww=qp(g,(mo-1)/n);
  w[0][0]=1;
  rep(i,1,n+1)w[0][i]=1ll*w[0][i-1]*ww%mo;
  rep(i,0,n+1)w[1][i]=w[0][n-i];
}

vector<int> conv(vector<int> a, vector<int> b) {
  int s = sz(a) + sz(b) - 1;
  if (s <= 0) return {};
  int L = s > 1 ? 32 - __builtin_clz(s-1) : 0, n = 1 << L;
  a.resize(n);
  b.resize(n);
  init(n);
  dft(&a[0],n,0);
  dft(&b[0],n,0);
  rep(i,0,n)a[i]=1ll*a[i]*b[i]%mo;
  dft(&a[0],n,1);
  a.resize(s);
  return a;
}

// a *= b
void mul(int *a,int *b,int n){
  static int x[N];
  rep(i,0,2*n)x[i]=b[i];
  init(2*n);
  dft(x,2*n,0);
  dft(a,2*n,0);
  rep(i,0,2*n)a[i]=1ll*x[i]*a[i]%mo;
  dft(a,2*n,1);
  rep(i,n,2*n)a[i]=0;
}

void inv(int *a,int n,int *b){
  static int x[N];
  b[0]=qp(a[0],mo-2);b[1]=0;
  for (int m=2;m<=n;m<<=1){
    rep(i,0,m) x[i]=a[i],x[i+m]=b[i+m]=0;
    init(2*m);
    dft(x,2*m,0);
    dft(b,2*m,0);
    rep(i,0,2*m) b[i]=1ll*b[i]*(2-1ll*x[i]*b[i]%mo+mo)%mo;
    dft(b,2*m,1);
    rep(i,m,2*m)b[i]=0;
  }
}

void Ln(int *a,int n){
  static int x[N];
  a[0]=1;inv(a,n,x);
  rep(i,0,n-1)a[i]=1ll*(i+1)*a[i+1]%mo;
  mul(a,x,n);
  per(i,1,n)a[i]=1ll*a[i-1]*qp(i,mo-2)%mo;
  a[0]=0;
}

void Exp(int *a,int n,int *r){
  static int x[N];
  r[0]=1;r[1]=0;
  for (int m=2;m<=n;m<<=1){
    rep(i,0,m)x[i]=r[i];
    Ln(x,m);
    rep(i,0,m)x[i]=(a[i]-x[i]+mo)%mo;
    x[0]=(x[0]+1)%mo;
    rep(i,m,2*m) r[i]=x[i]=0;
    mul(r,x,m);
    rep(i,m,2*m)r[i]=0;
  }
}
