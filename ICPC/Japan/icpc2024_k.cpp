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

int n, m, U[1<<20], C[1<<20], w[N_];
void Solve(){
    scanf("%d%d",&n,&m);
    rng(i,1,n){
        char p[30];
        scanf("%s",p);
        int s=0, c=0;
        rep(j,m){
            if(p[j]=='Y'){
                c++;
                s|=(1<<j);
            }
        }
        C[i] = c;
        w[i] = s;
        if(!U[s])U[s] = i;
    }
    per(i,(1<<m)){
        rep(j,m){
            if((i>>j)&1)continue;
            int x = U[i|(1<<j)];
            if(!x)continue;
            //printf("! %d %d\n",i,x);
            if(x){
                if(U[i] && (C[U[i]] > C[x] || (C[U[i]] == C[x] && U[i]<x)))continue;
                U[i] = x;
            }
        }
    }
    int Mx = -1;
    int r1=-1,r2=-1;
    rng(i,1,n){
        int a = U[(1<<m) -1 - w[i]];
        //printf("%d %d\n",i,a);
        if(a && Mx < C[i] + C[a]){
            Mx = C[i]+C[a];
            r1=i,r2=a;
        }
    }
    if(r1==-1){
        puts("No");
        return;
    }
    if(r1==r2){
        int pv=0;
        rng(i,1,n){
            if(i==r1)continue;
            if((w[r1]|w[i]) == (1<<m)-1){
                if(!pv || C[pv]<C[i])pv=i;
            }
        }
        r2 = pv;
    }
    printf("%d %d\n",min(r1,r2),max(r1,r2));
}
 
int main(){
    
    int TC=1;
    //scanf("%d",&TC);
    while(TC--){
        Solve();
    }
}
