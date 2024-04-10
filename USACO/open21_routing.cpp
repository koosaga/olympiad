#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int mod = 1e9 + 7; // 1e9 + 7;//993244853;

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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		vector<string> a(n);
		for (auto &x : a)
			cin >> x;
		vector<mint> inv(n + 1), fact(n + 1);
		fact[0] = 1;
		for (int i = 1; i <= n; i++) {
			inv[i] = mint(1) / mint(i);
			fact[i] = fact[i - 1] * mint(i);
		}
		vector<pi> backs;
		vector<int> indeg(n), outdeg(n), deg(n);
		for (int i = 0; i < n; i++)
			if (s[i] == 'S')
				deg[i] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] == '1') {
					deg[j]++;
					if (i > j)
						backs.push_back({i, j});
				}
			}
		}
		while (sz(backs) < 2)
			backs.push_back({-1, -1});
		auto fn = [&](int u, int v) {
			if (u < v || u == -1 || v == -1)
				return mint(0);
			vector<mint> dp(n);
			dp[v] = 1;
			for (int i = v; i <= u; i++) {
				if (deg[i])
					dp[i] *= inv[deg[i]];
				for (int j = i + 1; j <= u; j++) {
					if (a[i][j] == '1')
						dp[j] += dp[i];
				}
			}
			return dp[u];
		};
		mint m[2][2];
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				m[i][j] = fn(backs[i][0], backs[j][1]);
		mint ans = mint(1) - m[0][0] - m[1][1] + m[0][0] * m[1][1] - m[0][1] * m[1][0];
		for (int i = 0; i < n; i++) {
			ans *= fact[deg[i]];
		}
		cout << ans << "\n";
	}
}