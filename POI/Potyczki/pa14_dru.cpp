#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;
const int MAXT = 2100000;
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

struct cartesian{
	pi tree[MAXT];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(0, 0));
		for(int i=1; i<=n; i++) tree[i + lim] = pi(a[i], i);
		for(int i=lim; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(0, 0);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}cartesian;

using ans = pair<int, mint>;
int n, a[MAXN], b[MAXN], l[MAXN], lrev[MAXN];
ans dp[MAXN];

ans merge(ans a, ans b){
	if(a > b) swap(a, b);
	if(a.first == b.first) b.second += a.second;
	return b;
}

struct segForGet{
	ans tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, ans(-1e9, mint(0)));
	}
	void upd(int x, ans v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	ans qry(int s, int e){
		s += lim;
		e += lim;
		ans x(-1e9, mint(0));
		while(s < e){
			if(s%2 == 1) x = merge(tree[s], x), s++;
			if(e%2 == 0) x = merge(tree[e], x), e--;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) x = merge(tree[s], x);
		return x;
	}
}segForGet;

struct segForPut{
	ans tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, ans(-1e9, mint(0)));
	}
	void upd(int s, int e, ans x){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) tree[s] = merge(tree[s], x), s++;
			if(e%2 == 0) tree[e] = merge(tree[e], x), e--;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s] = merge(tree[s], x);
	}
	ans qry(int x){
		ans v(-1e9, mint(0));
		for(int i = x + lim; i; i >>= 1){
			v = merge(v, tree[i]);
		}
		return v;
	}
}segForPut;

void solve(int s, int e){
	if(s > e){
		dp[e] = merge(dp[e], segForPut.qry(e));
		segForGet.upd(e, dp[e]);
		return;
	}
	int v, m;
	tie(v, m) = cartesian.query(s, e);
	solve(s, m - 1);
	if(m - s >= e - m){
		for(int i = m; i <= e; i++){
			int lbnd = max(s, l[i]) - 1;
			int rbnd = min(m - 1, i - v);
			if(lbnd > rbnd) continue;
			auto qr = segForGet.qry(lbnd, rbnd);
			qr.first++;
			dp[i] = merge(dp[i], qr);
		}
	}
	else{
		for(int i = s - 1; i <= m - 1; i++){
			int lbnd = max(m, i + v);
			int rbnd = min(e, lrev[i  + 1]);
			if(lbnd > rbnd) continue;
			auto dpv = dp[i];
			dpv.first++;
			segForPut.upd(lbnd, rbnd, dpv);
		}
	}
	solve(m + 1, e);
}

struct rmq{
	int tree[MAXT], lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
		for(int i=1; i<=n; i++) tree[i + lim] = a[i];
		for(int i=lim; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq;

void solve(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		a[i] = 1;
		b[i] = n;
		while((i % (1 << a[i])) == 0) a[i]++;
		scanf("%d %d",&a[i],&b[i]);
	}
	cartesian.init(n, a);
	rmq.init(n, b);
	segForGet.init(n);
	segForPut.init(n);
	int j = 1;
	for(int i=1; i<=n; i++){
		while(rmq.query(j, i) < i - j + 1) j++;
		l[i] = j;
	}
	j = 1;
	for(int i=1; i<=n; i++){
		while(j < n && l[j+1] <= i) j++;
		lrev[i] = j;
	}
	for(int i=0; i<=n; i++){
		dp[i].first = (i == 0 ? 0 : -1e9);
		dp[i].second = mint(1);
	}
	solve(1, n);
	auto qr = dp[n];
	if(qr.first < 0) puts("NIE");
	else printf("%d %lld\n", qr.first, (lint)qr.second);
}

int main(){
	solve();
}
