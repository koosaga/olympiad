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
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<pi> a(n);
		vector<int> cnt(2 * n + 1);
		for (auto &[x, y] : a) {
			cin >> x >> y;
			x--;
			y--;
			cnt[x]++;
			cnt[y]--;
		}
		for (int i = 1; i <= 2 * n; i++)
			cnt[i] += cnt[i - 1];
		sort(all(a));
		vector<int> stk;
		vector<vector<int>> gph(n + 1);
		for (int i = 0; i < n; i++) {
			while (sz(stk) && a[stk.back()][1] < a[i][0]) {
				stk.pop_back();
			}
			int par = (sz(stk) ? stk.back() : -1);
			gph[par + 1].push_back(i + 1);
			//	cout << par + 1 << " " << i + 1 << endl;
			stk.push_back(i);
		}
		vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, mint(1)));
		for (int i = n; i >= 0; i--) {
			for (auto &k : gph[i]) {
				for (int j = 0; j <= n; j++) {
					dp[i][j] *= dp[k][j];
				}
			}
			if (i > 0) {
				for (int j = 0; j < n; j++) {
					dp[i][j] = dp[i][j] * mint(cnt[a[i - 1][1]] + 1 - j) - dp[i][j + 1];
				}
			}
		}
		cout << dp[0][0] << "\n";
	}
}