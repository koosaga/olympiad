#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
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

mint sum[21][1 << 20];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> msk(n);
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == 'E')
				msk[j] |= (1 << i);
		}
	}
	vector<mint> fact(n + 1), invf(n + 1);
	fact[0] = invf[0] = 1;
	for (int i = 1; i <= n; i++) {
		fact[i] = fact[i - 1] * mint(i);
		invf[i] = mint(1) / fact[i];
	}
	vector<mint> dp(1 << m);
	vector<int> cnt(1 << m);
	for (auto &x : msk)
		cnt[x]++;
	vector<vector<int>> m2c(m + 1);
	for (int i = 0; i < (1 << m); i++)
		m2c[__builtin_popcount(i)].push_back(i);
	for (int c = 0; c <= m; c++) {
		for (auto &i : m2c[c]) {
			mint f = 0;
			for (int j = 1; j <= cnt[i]; j++)
				f += invf[j - 1];
			f *= fact[cnt[i]];
			dp[i] = 1;
			for (int k = c - 1; k >= 0; k--)
				dp[i] += sum[k][i];
			dp[i] *= f;
			sum[c][i] = dp[i];
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < (1 << m); j++) {
				if ((j >> i) & 1)
					sum[c][j] += sum[c][j - (1 << i)];
			}
		}
	}
	cout << accumulate(all(dp), mint(0)) << "\n";
}