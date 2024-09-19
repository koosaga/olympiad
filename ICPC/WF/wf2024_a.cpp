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
using Mint = ModInt<1000000007>;
template<> const Mint Mint::G = Mint(3);
using a3 = array<int,3>;

int n, L, vis[5010];
long double Z[5010][5010];
pii U[5010];
ll S[5010];

int main(){
    scanf("%d%d",&n,&L);
    rng(i,1,n){
        int m;
        scanf("%d",&m);
        rep(j,m){
            scanf("%d%d",&U[j].fi,&U[j].se);
        }
        rng(j,1,m-1){
            S[j] = S[j-1] + 1ll *(U[j].se + U[j-1].se) * (U[j].fi - U[j-1].fi);
        }
        Z[i][n] = L;

        int pv = 0;
        rng(j,1,n-1){
            while(S[pv+1] * n <= S[m-1] * j) pv++;

            if(S[pv] * n == S[m-1] * j){
                Z[i][j] = U[pv].fi;
                continue;
            }

            long double d = ((long double)U[pv+1].se - U[pv].se) / (U[pv+1].fi - U[pv].fi);

//             -  == 2*U[pv]*x +  d * x*x

            long double AA = d;
            long double BB = 2*U[pv].se;

            long double CC = S[pv] - (long double)S[m-1] * j / n;
            long double xx;
            if(U[pv+1].se == U[pv].se){
                xx = (long double)(-CC / BB);
            }

            else{
                xx = (-BB + sqrtl(max(BB*BB-4*AA*CC,0.0L)))/(2*AA);
            }
           // printf("%Lf\n",xx);
            Z[i][j] = U[pv].fi + xx;

//U[pv], U[pv+1]

        }
        //rng(j,1,n)printf("%f ",Z[i][j]);
        //puts("");
    }
    rng(i,1,n){
        long double Mn = L+1;
        int pv=-1;
        rng(j,1,n){
            if(!vis[j] && Mn > Z[j][i]){
                Mn = Z[j][i];
                pv=j;
            }
        }
        printf("%.15Lf %d\n",Mn,pv);
        vis[pv]=1;
    }
}