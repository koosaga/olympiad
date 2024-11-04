#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;
const int mod = 998244353; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
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

struct seg {
	int tree[MAXT], lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i] += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = min(tree[2 * p], tree[2 * p + 1]);
	}
	lint dfs(int s, int e, int p, int n) {
		if (tree[p] > 0)
			return 0;
		if (s == e)
			return 1ll * s * (n - s);
		if (2 * e <= n) {
			while (s != e) {
				lazydown(p);
				int m = (s + e) / 2;
				if (tree[2 * p + 1] == 0)
					s = m + 1, p = 2 * p + 1;
				else
					e = m, p = 2 * p;
			}
			return 1ll * s * (n - s);
		}
		if (2 * s >= n) {
			while (s != e) {
				lazydown(p);
				int m = (s + e) / 2;
				if (tree[2 * p] > 0)
					s = m + 1, p = 2 * p + 1;
				else
					e = m, p = 2 * p;
			}
			return 1ll * s * (n - s);
		}
		lazydown(p);
		int m = (s + e) / 2;
		return max(dfs(s, m, 2 * p, n), dfs(m + 1, e, 2 * p + 1, n));
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> edges;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (u > v)
			swap(u, v);
		edges.push_back({u - 1, v - 1});
	}
	lint ans = 0;
	// case 1: remove one M
	{
		for (int i = 0; i < m; i++) {
			seg.add(edges[i][0] + 1, edges[i][1], 1, n - 1, 1, +1);
		}
		for (int i = 0; i < m; i++) {
			seg.add(edges[i][0] + 1, edges[i][1], 1, n - 1, 1, -1);
			ans = max(ans, seg.dfs(1, n - 1, 1, n));
			seg.add(edges[i][0] + 1, edges[i][1], 1, n - 1, 1, +1);
		}
	}
	// case 4: divide it into subsegment
	{
		priority_queue<int, vector<int>, greater<int>> pqmin;
		priority_queue<int> pqmax;
		vector<vector<int>> g1(n), g2(n);
		vector<int> L(n), R(n);
		for (auto &[u, v] : edges) {
			g1[u].push_back(v);
			g2[v].push_back(u);
		}
		for (int i = 1; i < n; i++) {
			for (auto &j : g1[i - 1])
				pqmin.push(j);
			while (sz(pqmin) && pqmin.top() < i)
				pqmin.pop();
			L[i] = (sz(pqmin) ? pqmin.top() : (n - 1));
		}
		for (int i = n - 1; i > 0; i--) {
			for (auto &j : g2[i])
				pqmax.push(j);
			while (sz(pqmax) && pqmax.top() >= i)
				pqmax.pop();
			R[i] = (sz(pqmax) ? pqmax.top() : -1);
		}
		set<int> s;
		vector<pi> vect;
		for (int i = 1; i <= n - 1; i++) {
			vect.push_back({R[i], i});
		}
		sort(all(vect));
		int p = 0;
		for (int i = 1; i <= n - 1; i++) {
			while (p < sz(vect) && vect[p][0] < i)
				s.insert(vect[p++][1]);
			// [i + 1, L[i]]
			auto j = s.lower_bound(L[i] + 1);
			if (j == s.begin())
				continue;
			j--;
			if (*j > i)
				ans = max(ans, 1ll * (*j - i) * (n - *j + i));
			if ((*j - i) * 2 >= n) {
				auto j = s.lower_bound(i + n / 2);
				ans = max(ans, 1ll * (*j - i) * (n - *j + i));
				if (j != s.begin()) {
					j--;
					if (*j > i)
						ans = max(ans, 1ll * (*j - i) * (n - *j + i));
				}
			}
		}
	}
	// remove zeros
	{
		vector<int> dx(n);
		for (auto &[u, v] : edges)
			dx[u]++, dx[v]--;
		for (int i = 1; i < n; i++)
			dx[i] += dx[i - 1];
		lint le = 0;
		for (int i = 0; i < n - 1; i++) {
			if (dx[i] == 0) {
				ans = max(ans, 1ll * (i + 1) * (n - i - 1) + le);
				le = max(le, 1ll * (i + 1) * (n - i - 1));
			}
		}
	}
	cout << 2 * ans << "\n";
}