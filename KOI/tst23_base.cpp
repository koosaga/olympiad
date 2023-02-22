#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 250005;

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = (lint)val * m.val % mod;
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	friend mint inv(const mint &a) {
		assert(a.val);
		return ipow(a, mod - 2);
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

vector<pi> gph[MAXN];
int sz[MAXN], din[MAXN], dout[MAXN], rev[MAXN], piv;
mint pae[MAXN];

void dfs(int x) {
	sz[x] = 1;
	for (auto &[w, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pi{w, x}));
		pae[y] = mint(w);
		dfs(y);
		sz[x] += sz[y];
	}
	sort(all(gph[x]), [&](pi &a, pi &b) { return sz[a[1]] > sz[b[1]]; });
}

void label(int x) {
	din[x] = piv++;
	rev[din[x]] = x;
	for (auto &[_, y] : gph[x]) {
		label(y);
	}
	dout[x] = piv;
}

set<pi> s;
lint sum;
lint tot;

lint gsz(pi a) {
	lint s = a[1] - a[0];
	return s * (s + 1) / 2;
}

void flip(int x, int v) {
	auto it = --s.lower_bound({x + 1, -1});
	auto cur = *it;
	sum -= gsz(cur);
	int l = x, r = x + 1;
	if (it != s.begin() && cur[0] == x) {
		sum -= gsz(*prev(it));
		l = (*prev(it))[0];
		s.erase(prev(it));
	}
	if (next(it) != s.end() && cur[1] == x + 1) {
		sum -= gsz(*next(it));
		r = (*next(it))[1];
		s.erase(next(it));
	}
	s.erase(it);
	auto ins = [&](int a, int b) {
		pi toIns = {a, b};
		sum += gsz(toIns);
		s.insert(toIns);
	};
	ins(l, r);
	if (cur[0] < x)
		ins(cur[0], x);
	if (cur[1] > x + 1)
		ins(x + 1, cur[1]);
}

mint query() { return tot - sum; }

mint solve(int x) {
	mint ans = pae[x] * query();
	flip(x, 1);
	if (sz(gph[x]) == 0)
		return ans;
	for (int i = dout[gph[x][0][1]]; i < dout[x]; i++)
		flip(rev[i], 1);
	ans += solve(gph[x][0][1]);
	for (int i = 1; i < sz(gph[x]); i++) {
		for (int j = din[gph[x][i][1]]; j < dout[gph[x][i][1]]; j++) {
			flip(rev[j], 0);
		}
		ans += solve(gph[x][i][1]);
	}
	return ans;
}

int maintenance_costs_sum(vector<int> U, vector<int> V, vector<int> W) {
	int n = sz(U) + 1;
	tot = 1ll * n * (n + 1) / 2;
	sum = 1ll * n * (n + 1) / 2;
	s.insert({0, n});
	for (int i = 0; i < sz(U); i++) {
		gph[U[i]].push_back({W[i], V[i]});
		gph[V[i]].push_back({W[i], U[i]});
	}
	dfs(0);
	label(0);
	return solve(0).val;
}
