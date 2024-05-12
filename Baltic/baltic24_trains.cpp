#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
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
	int n;
	cin >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	vector<mint> dp(n);
	vector<vector<mint>> sums(100, vector<mint>(n));
	for (int i = n - 1; i >= 0; i--) {
		dp[i] = 1;
		if (a[i][0] >= 100) {
			for (int j = 1; i + j * a[i][0] < n && j <= a[i][1]; j++)
				dp[i] += dp[i + j * a[i][0]];
		} else if (a[i][0] > 0) {
			if (i + a[i][0] < n)
				dp[i] += sums[a[i][0]][i + a[i][0]];
			if (i + 1ll * a[i][0] * (a[i][1] + 1) < n)
				dp[i] -= sums[a[i][0]][i + 1ll * a[i][0] * (a[i][1] + 1)];
		}
		for (int j = 1; j < 100; j++)
			sums[j][i] = (i + j < n ? sums[j][i + j] : mint(0)) + dp[i];
	}
	cout << dp[0] << "\n";
}