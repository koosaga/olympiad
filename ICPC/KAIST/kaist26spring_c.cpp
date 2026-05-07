#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

const int mod = 998244353; // 1e9 + 7;//993244853;

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

vector<mint> go(vector<mint> a) {
	vector<mint> dp(1);
	dp[0] = 1;
	for (auto &x : a) {
		vector<mint> nxt(sz(dp) + 1);
		for (int j = 0; j < sz(dp); j++) {
			nxt[j] += dp[j] * (mint(1) - x);
			nxt[j + 1] += dp[j] * x;
		}
		dp = nxt;
	}
	return dp;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> adj(n, vector<int>(n));
	vector<mint> p(n);
	for (int i = 0; i < n; i++)
		cin >> p[i].val, adj[i][i] = 1;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u - 1][v - 1] = adj[v - 1][u - 1] = 1;
	}
	vector<mint> A, B, C;
	for (int i = 0; i < n; i++) {
		if (adj[0][i] && adj[1][i]) {
			A.push_back(p[i]);
		} else if (adj[0][i])
			B.push_back(p[i]);
		else if (adj[1][i])
			C.push_back(p[i]);
	}
	A = go(A);
	B = go(B);
	C = go(C);
	while (q--) {
		int s, t;
		cin >> s >> t;
		mint ans = 0;
		for (int x = 0; x <= min(s, t); x++) {
			int y = s - x, z = t - x;
			if (y >= sz(B) || z >= sz(C) || x>= sz(A))
				continue;
			ans += A[x] * B[y] * C[z];
		}
		cout << ans << "\n";
	}
}
