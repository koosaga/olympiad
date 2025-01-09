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


const int SZ = (1<<18);
#define N_ 401000

int n;
ll d,r;
int D[510][510];
bitset<501> U[510][510];
ll S[510], w[510], DD[510];
void Solve(){
    scanf("%d%lld%lld",&n,&d,&r);
    rng(i,1,n){
        scanf("%lld",&w[i]);
        S[i]=S[i-1]+w[i];
    }
    rng(l,0,n-1){
        rng(b,1,n-l){
            int e = b+l;
            if(b<e)U[b][e] = U[b+1][e];
            ll s = S[e]-S[b-1];
            if(s%d == r){
                D[b][e]=1;
                U[b][e][1]=1;
            }
            rng(k,b,e-1){
                if(D[b][k]){
                    U[b][e][D[b][k]]=1;
                    U[b][e] |= (U[k+1][e] << D[b][k]);
                }
            }
            rng(k,1,l+1){
                if(U[b][e][k]==1 && (s - r*k)%d == r){
                    if(!D[b][e] || D[b][e]>k+1)D[b][e]=k+1;
                }
            }
            //rng(k,1,l+1)printf("%d",!!U[b][e][k]);
            //puts("");
            //printf("%d %d %d\n",b,e,D[b][e]);
        }
    }
    rng(i,1,n){
        DD[i]=DD[i-1];
        rng(j,1,i){
            if(D[j][i]){
                DD[i] = max(DD[i], DD[j-1] + (S[i]-S[j-1] - D[j][i]*r)/d);
            }
        }
    }
    printf("%lld\n",DD[n]);
}
 
int main(){
    
    int TC=1;
    //scanf("%d",&TC);
    while(TC--){
        Solve();
    }
}
