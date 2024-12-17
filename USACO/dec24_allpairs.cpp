#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 1e9 + 7;

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

lint binom[69][69];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q, n;
	cin >> q >> n;
	vector<int> pcnt(1 << n);
	vector<mint> invs(n + 1);
	for (int i = 0; i <= n; i++) {
		binom[i][0] = 1;
		if (i)
			invs[i] = mint(1) / mint(i);
		for (int j = 1; j <= i; j++)
			binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
	}
	for (int i = 1; i < sz(pcnt); i++) {
		pcnt[i] = pcnt[i - (i & -i)] + 1;
	}
	vector<int> a(q);
	for (auto &x : a) {
		cin >> x;
	}
	vector<int> dp(1 << n);
	for (auto &x : a) {
		dp[x]++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((j >> i) & 1) {
				dp[j ^ (1 << i)] += dp[j];
			}
		}
	}
	vector<vector<lint>> sum(n + 1, vector<lint>(1 << n));
	for (int k = 0; k <= n; k++) {
		for (int j = 0; j < (1 << n); j++) {
			sum[k][j] = binom[pcnt[j]][k] * (pcnt[j] % 2 != k % 2 ? -1 : 1) * dp[j];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < (1 << n); j++) {
				if ((j >> i) & 1) {
					sum[k][j] += sum[k][j ^ (1 << i)];
				}
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < (1 << n); j++)
			sum[i][j] += sum[i + 1][j];
	}
	for (int i = 0; i < q; i++) {
		mint ans = 0;
		int inv = (1 << n) - 1 - a[i];
		vector<lint> inside(pcnt[inv] + 1);
		for (int m = 0; m < n; m++) {
			if ((a[i] >> m) & 1) {
				for (int x = 0; x < sz(inside); x++) {
					inside[x] += sum[x + 1][inv | (1 << m)] - sum[x + 1][inv];
				}
			}
		}
		for (int x = 0; x < sz(inside); x++) {
			ans += mint(inside[x]) * invs[pcnt[a[i]] + x];
		}
		cout << ans << "\n";
	}
}