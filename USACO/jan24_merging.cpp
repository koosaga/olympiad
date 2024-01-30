
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 5005;
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

mint inv[MAXN];
int a[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = a[i - 1] + x;
		inv[i] = mint(1) / mint(i);
	}
	vector<vector<mint>> dp(n + 1, vector<mint>(n + 1));
	vector<vector<mint>> sum(n + 2, vector<mint>(n + 1));
	for (int i = 1; i <= n; i++) {
		int k = 1;
		int l = n;
		vector<mint> ps(n + 2);
		for (int j = n; j >= i; j--) {
			if (i == 1 && j == n) {
				dp[i][j] = sum[i][j] = ps[j] = inv[n - 1];
				continue;
			}
			while (a[l] >= 2 * a[j] - a[i - 1])
				l--;
			dp[i][j] = ps[j + 1] - ps[l + 1];
			while (k < i && 2 * a[i - 1] - a[j] > a[k - 1])
				k++;
			dp[i][j] += sum[i - 1][j] - sum[k - 1][j];
			if (i != j)
				dp[i][j] *= inv[j - i];
			sum[i][j] = sum[i - 1][j] + dp[i][j];
			ps[j] = ps[j + 1] + dp[i][j];
		}
	}
	for (int i = 1; i <= n; i++)
		cout << dp[i][i] << "\n";
}