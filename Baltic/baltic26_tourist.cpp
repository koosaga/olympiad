#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 1e9 + 7;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// Polynomial composition is due to ecnerwala:
// https://judge.yosupo.jp/submission/336262
// To use polynomial sqrt, need to amend sqrt for modint.

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
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

const int MAXN = 200005;
vector<vector<int>> gph;
int par[19][MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;

bool in(int u, int v) { return din[u] <= din[v] && dout[v] <= dout[u]; }

void dfs(int x, int p = -1) {
	din[x] = piv++;
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			par[0][y] = x;
			dfs(y, x);
		}
	}
	dout[x] = piv;
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1)
			v = par[i][v];
		dx >>= 1;
	}
	if (u == v)
		return u;
	for (int i = 18; i >= 0; i--) {
		if (par[i][u] != par[i][v])
			u = par[i][u], v = par[i][v];
	}
	return par[0][u];
}

mint dp[10005][205];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	disj.init(n);
	cr(gph, n);
	vector<int> C = {0, n - 1};
	vector<pi> B;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (disj.uni(u, v)) {
			gph[u].push_back(v);
			gph[v].push_back(u);
		} else {
			C.push_back(u);
			C.push_back(v);
			B.push_back({u, v});
		}
	}
	dfs(0);
	for (int i = 1; i < 19; i++) {
		for (int j = 0; j < n; j++)
			par[i][j] = par[i - 1][par[i - 1][j]];
	}
	vector<array<int, 3>> edges;
	{
		sort(all(C), [&](int a, int b) { return din[a] < din[b]; });
		C.resize(unique(all(C)) - C.begin());
		int z = sz(C) - 1;
		for (int i = 0; i < z; i++) {
			C.push_back(lca(C[i], C[i + 1]));
		}
		sort(all(C), [&](int a, int b) { return din[a] < din[b]; });
		C.resize(unique(all(C)) - C.begin());
		vector<int> stk;
		for (int i = 0; i < sz(C); i++) {
			while (sz(stk) && !in(stk.back(), C[i]))
				stk.pop_back();
			if (sz(stk)) {
				edges.push_back({stk.back(), C[i], dep[C[i]] - dep[stk.back()]});
			}
			stk.push_back(C[i]);
		}
	}
	for (auto &[u, v] : B)
		edges.push_back({u, v, 1});
	{
		int d = sz(edges);
		vector<array<int, 3>> tt;
		for (int k = 0; k < d; k++) {
			auto v = edges[k];
			tt.push_back(v);
			swap(v[0], v[1]);
			tt.push_back(v);
		}
		edges = tt;
	}
	assert(sz(edges) <= 200);
	dp[0][sz(edges)] = 1;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j <= sz(edges); j++) {
			int e = (j < sz(edges) ? edges[j][1] : 0);
			for (int x = 0; x < sz(edges); x++) {
				auto [u, v, w] = edges[x];
				if (u == e && x / 2 != j / 2 && i + w <= k)
					dp[i + w][x] += dp[i][j];
			}
		}
	}
	mint sum = 0;
	for (int i = 0; i < sz(edges); i++) {
		if (edges[i][1] == n - 1)
			sum += dp[k][i];
	}
	cout << sum << "\n";
}