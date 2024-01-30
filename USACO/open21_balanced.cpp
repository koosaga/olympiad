#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 155;
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

mint dp[MAXN][MAXN][2][2];
mint sum[MAXN][MAXN][2][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<string> a(n);
	for (auto &x : a)
		cin >> x;
	mint ans;
	auto gsum = [&](int p, int q, int sx, int ex, int sy, int ey) { return sum[ex + 1][ey + 1][p][q] - sum[sx][ey + 1][p][q] - sum[ex + 1][sy][p][q] + sum[sx][sy][p][q]; };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = j; k < n; k++) {
				if (a[i][k] == '.')
					break;
				dp[j][k][0][0] += gsum(0, 0, 0, j, k, n - 1);
				dp[j][k][0][0] += gsum(0, 1, 0, j, j, k - 1);
				dp[j][k][0][0] += gsum(1, 0, j + 1, k, k, n - 1);
				dp[j][k][0][0] += gsum(1, 1, j + 1, k, j, k - 1);
				dp[j][k][0][1] += gsum(0, 1, 0, j, j, k);
				dp[j][k][0][1] += gsum(1, 1, j + 1, n - 1, j, k);
				dp[j][k][1][0] += gsum(1, 0, j, k, k, n - 1);
				dp[j][k][1][0] += gsum(1, 1, j, k, 0, k - 1);
				dp[j][k][1][1] += gsum(1, 1, j, k, j, k);
				dp[j][k][0][0] += mint(1);
				dp[j][k][0][1] += mint(1);
				dp[j][k][1][0] += mint(1);
				dp[j][k][1][1] += mint(1);
				ans += dp[j][k][0][0];
			}
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				for (int a = 0; a < 2; a++) {
					for (int b = 0; b < 2; b++) {
						sum[j + 1][k + 1][a][b] = sum[j][k + 1][a][b] + sum[j + 1][k][a][b] - sum[j][k][a][b] + dp[j][k][a][b];
						dp[j][k][a][b] = 0;
					}
				}
			}
		}
	}
	cout << ans << "\n";
}