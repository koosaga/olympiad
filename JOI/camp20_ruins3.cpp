#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1222;
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

mint binom[MAXN][MAXN], fact[MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	for (int i = 0; i < MAXN; i++) {
		binom[i][0] = 1;
		fact[i] = (i ? (fact[i - 1] * mint(i)) : mint(1));
		for (int j = 1; j <= i; j++)
			binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
	}
	int n;
	cin >> n;
	vector<int> a(2 * n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x - 1] = 1;
	}
	vector<mint> dp(n + 1);
	dp[n] = 1;
	int yes = 0, no = 0;
	for (int i = 0; i < 2 * n; i++) {
		vector<mint> nxt(n + 1);
		for (int j = 0; j <= n; j++) {
			if (a[i]) {
				if (n - j - yes > 0)
					nxt[j] += dp[j] * mint(n - j - yes);
			} else {
				nxt[j] += dp[j];
				if (no - (n - j) < 0)
					continue;
				for (int k = 0; k < j; k++) {
					nxt[k] += dp[j] * binom[2 * (j - k)][j - k] * binom[no - (n - j)][j - k - 1] * fact[j - k - 1];
				}
			}
		}
		dp = nxt;
		if (a[i])
			yes++;
		else
			no++;
	}
	cout << dp[0] / ipow(mint(2), n) << "\n";
}