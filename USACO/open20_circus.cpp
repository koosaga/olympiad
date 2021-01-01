#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i) ret += tree[i];
		return ret;
	}
	void clear(int x){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] = 0;
	}
}bit;

mint fact[MAXN], invf[MAXN];

int n, sz[MAXN], dep[MAXN], par[MAXN], cpar[MAXN];
vector<int> gph[MAXN], cond[MAXN];

void dfs(int x, int p = -1){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			par[i] =x ;
			dep[i] = dep[x] + 1;
			dfs(i, x);
			sz[x] += sz[i];
		}
	}
}

int rt;
int a[MAXN], b[MAXN];
vector<int> event[MAXN];
int din[MAXN], dout[MAXN], piv;

void dfs2(int x){
	a[x] = n - (sz[x] + dep[x] - dep[cpar[x]]);
	b[x] = sz[x] - 1;
	din[x] = ++piv;
	for(auto &i : cond[x]){
		dfs2(i);
	}
	if(rt != x){
		for(int k = a[x] + b[x]; k < n; k++){
			event[k].push_back(x);
		}
	}
	dout[x] = piv;
}

void solve(){
	for(int i=0; i<MAXN; i++){
		event[i].clear();
		gph[i].clear();
		cond[i].clear();
	}
	piv = 0;
	scanf("%d",&n);
	fact[0] = invf[0] = 1;
	for(int i=1; i<=n; i++){
		fact[i] = fact[i-1] * mint(i);
		invf[i] = mint(1) / fact[i];
	}
	for(int i=0; i<n-1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	rt = 1;
	while(sz(gph[rt]) >= 2) rt++;
	dep[rt] = 0;
	dfs(rt);
	for(int i=1; i<=n; i++){
		if(i != rt && sz(gph[i]) != 2){
			int j = par[i];
			while(sz(gph[j]) == 2) j = par[j];
			cpar[i] = j;
			cond[j].push_back(i);
		}
	}
	dfs2(rt);
	for(int k = 1; k <= n - 1; k++){
		mint ret = fact[k];
		for(auto &j : event[k]){
			int ans = bit.query(dout[j]) - bit.query(din[j]);
			ret *= invf[b[j] - ans];
			bit.add(din[j], (k - a[j]) - ans);
		}
		int rt = bit.query(n);
		ret *= invf[k - rt];
		printf("%lld\n", (lint)ret);
		for(auto &j : event[k]) bit.clear(din[j]);
	}
	printf("%lld\n", (lint)fact[n]);
}

int main(){
	solve();
}
