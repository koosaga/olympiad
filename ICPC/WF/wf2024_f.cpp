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

int n, UF[1010], C[1010];
struct point{
    ll x, y;
}w[1010];
int Find(int a){
    if(a==UF[a])return a;
    return UF[a]=Find(UF[a]);
}
bool Merge(int a, int b){
    a=Find(a),b=Find(b);
    if(a==b)return false;
    UF[a]=b;
    C[b]+=C[a];
    return true;
}
bool OK(vi Z){
    bitset<1000>B;
    B.reset();
    B[0]=1;
    for(auto &x:Z)B |= (B<<x);
    return B[n/2] == 1;
}
int D[1010][1010], vis[1010];
pii P[1010][1010];
void Print(){
    int cnt = 0;
    D[0][0]=1;
    rng(i,1,n){
        if(Find(i)==i){
            cnt++;
           // printf("%d\n",C[i]);
            int x = C[i];
            rng(j,0,n){
                if(D[cnt-1][j]){
                    D[cnt][j+x] = 1;
                    P[cnt][j+x] = {j,i};
                    D[cnt][j] = 1;
                    P[cnt][j] = {j,0};
                }
            }
        }
    }
    //puts("??");
    //printf("%d\n",D[cnt][n/2]);
    int x = cnt, y = n/2;
    while(x){
        vis[P[x][y].se]=1;
        y=P[x][y].fi;
        //printf("%d\n",P[x][y].se);
        x--;
    }
    rng(i,1,n){
        if(vis[Find(i)])printf("%d\n",i);
    }
}
int main(){
    scanf("%d",&n);
    n*=2;
    rng(i,1,n){
        scanf("%lld%lld",&w[i].x,&w[i].y);
    }
    rng(i,1,n)UF[i]=i,C[i]=1;
    vc<array<ll,3>>Z;
    rng(i,1,n){
        rng(j,1,i-1){
            Z.pb({(w[i].x-w[j].x)*(w[i].x-w[j].x) + (w[i].y-w[j].y)*(w[i].y-w[j].y), i, j});
        }
    }
    sort(all(Z));
    for(auto &[d,a,b]: Z){
        if(Find(a)!=Find(b)){
            int aa = Find(a), bb = Find(b);
            vi Z;
            rng(i,1,n){
                if(i!=aa && i!=bb && UF[i]==i)Z.pb(C[i]);
            }
            Z.pb(C[aa]+C[bb]);
            if(!OK(Z)){
                printf("%.10f\n",sqrt(d));
                Print();
                return 0;
            }
            else{
                Merge(a,b);
            }
        }
    }
}