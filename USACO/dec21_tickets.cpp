#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 5005;
const int MAXT = 270000;
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

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(-1e18, -1));
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e18, -1);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

struct tickets{
	int c, p, l, r;
};

void get_distance(int n, vector<tickets> tick, vector<lint> &dist){
	vector<int> ptr(n);
	seg.init(sz(tick));
	for(int i = 0; i < sz(tick); i++){
		seg.upd(i, pi(tick[i].r, i));
		ptr[tick[i].l]++;
	}
	for(int i = 1; i < n; i++) ptr[i] += ptr[i - 1];
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i = 0; i < n + sz(tick); i++){
		pq.emplace(dist[i], i);
	}
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		if(x.second >= n){
			int idx = x.second - n;
			if(dist[tick[idx].p] > dist[x.second] + tick[idx].c){
				dist[tick[idx].p] = dist[x.second] + tick[idx].c;
				pq.emplace(dist[tick[idx].p], tick[idx].p);
			}
		}
		else{
			pi q;
			while((q = seg.query(0, ptr[x.second] - 1)).first >= x.second){
				int idx = q.second;
				seg.upd(idx, pi(-1e18, -1));
				if(dist[idx + n] > dist[x.second]){
					dist[idx + n] = dist[x.second];
					pq.emplace(dist[idx + n], idx + n);
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<tickets> tick(k);
	for(auto &i : tick){
		cin >> i.p >> i.c >> i.l >> i.r;
		i.p--;
		i.l--;
		i.r--;
	}
	sort(all(tick), [&](const tickets &a, const tickets &b){
		return pi(a.l, a.r) < pi(b.l, b.r);
	});
	vector<lint> d0(n + k, 1e18), d1(n + k, 1e18), sol(n + k);
	d0[0] = d1[n - 1] = 0;
	get_distance(n, tick, d0);
	get_distance(n, tick, d1);
	for(int i = 0; i < n + k; i++) sol[i] = d0[i] + d1[i];
	get_distance(n, tick, sol);
	sol.resize(n);
	for(auto &i : sol){
		if(i > 1e17) i = -1;
		cout << i << '\n';
	}
}

