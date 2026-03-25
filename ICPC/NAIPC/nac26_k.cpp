//ainta
#include <bits/stdc++.h>
using namespace std;
 
#define rng(i,a,b) for(int i=int(a);i<=int(b);i++)
#define rep(i,b) rng(i,0,b-1)
#define gnr(i,b,a) for(int i=int(b);i>=int(a);i--)
#define per(i,b) gnr(i,b-1,0)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#define si(x) int(x.size())
template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;
typedef long long ll;
using pii=pair<int,int>;
using vi=vc<int>;
using uint=unsigned;
using ull=unsigned long long;
using pil=pair<int,ll>;
using pli=pair<ll,int>;
using pll=pair<ll,ll>;
using t3=tuple<int,int,int>;
using namespace std;


 
ll rand_int(ll l, ll r) { //[l, r]
	#ifdef LOCAL
	static mt19937_64 gen;
	#else
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    #endif
    return uniform_int_distribution<ll>(l, r)(gen);
}
 
 
template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;
template<> const Mint Mint::G = Mint(3);
 
template <class Mint> void nft(bool type, vc<Mint>& a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) s++;
    assert(1 << s == n);
 
    static vc<Mint> ep, iep;
    while (int(ep.size()) <= s) {
        ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }
    vc<Mint> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << (s - i);
        Mint base = type ? iep[i] : ep[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

 
template <class Mint> vc<Mint> multiply(const vc<Mint>& a, const vc<Mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if(n<30 || m<30){
        vc<Mint> ret(n+m-1);
        rep(i,n)rep(j,m)ret[i+j] += a[i]*b[j];
        return ret;
    }
    int lg = 0;
    while ((1 << lg) < n + m - 1) lg++;
    int z = 1 << lg;
    auto a2 = a, b2 = b;
    a2.resize(z);
    b2.resize(z);
    nft(false, a2);
    nft(false, b2);
    for (int i = 0; i < z; i++) a2[i] *= b2[i];
    nft(true, a2);
    a2.resize(n + m - 1);
    Mint iz = Mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
    return a2;
}

#define N_ 201000
const int SZ = (1<<18);
int n;
struct point{
    ll x, y;
}w[410];
int ccw(point a, point b, point c){
    ll t = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
    return t==0?0:t>0?1:-1;
}
__int128 A[400][400], B[400][400];
bool Do(__int128 mask){
    //printf("%lld\n",mask);
    int c=0;
    rep(i,n){
        if((mask>>i)&1)c++;
    }
    if(c<=1)return true;
    rep(i,4*n){
        rep(j,i){
            if((A[i][j]&mask) && (B[i][j]&mask) && ((A[i][j]|B[i][j])&mask) ==mask){
                return Do(A[i][j]&mask) && Do(B[i][j]&mask);
            }
        }
    }
    return false;
}
void Solve(){
    scanf("%d",&n);
    rep(i,n){
        int bx,by,ex,ey;
        scanf("%d%d%d%d",&bx,&by,&ex,&ey);
        w[i*4] = {bx,by};
        w[i*4+1] = {bx,ey};
        w[i*4+2] = {ex,ey};
        w[i*4+3] = {ex,by};
    }
    rep(i,4*n){
        rep(j,i){
            rep(k,n){
                __int128 a=1, b=1;
                a<<=k, b<<=k;
                rep(l,4){
                    int ck = ccw(w[i],w[j],w[k*4+l]);
                    if(ck==-1) a=0;
                    if(ck==1) b=0;
                }
                A[i][j]|=a;
                B[i][j]|=b;
            }
        }
    }
    __int128 z = 1;
    z<<=n;
    z-=1;
    if(Do(z))printf("%d\n",n-1);
    else printf("impossible\n");
}

int main(){
	int TC=1;
    //scanf("%d",&TC);
    rng(T,1,TC){
        Solve();
    }
}

