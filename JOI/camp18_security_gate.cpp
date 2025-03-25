#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 305;

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

mint d1[MAXN][MAXN][MAXN];
mint d2[MAXN][MAXN];
mint d3[MAXN][MAXN * 2][3];

mint f(string s, int d) {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			d2[i][j] = 0;
			for (int k = 0; k < MAXN; k++)
				d1[i][j][k] = 0;
		}
	}
	d1[0][0][0] = 1;
	int n = sz(s);
	mint ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			for (int k = 0; k <= i; k++) {
				if (s[i] != '(') {
					if (j > 0)
						d1[i + 1][j - 1][k] += d1[i][j][k];
					else
						d2[i + 1][k] += d1[i][j][k];
				}
				if (s[i] != ')') {
					d1[i + 1][j + 1][max(k, j + 1)] += d1[i][j][k];
				}
			}
		}
	}
	for (int h = 1; h <= n; h++) {
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < 2 * MAXN; j++) {
				for (int k = 0; k < 3; k++) {
					d3[i][j][k] = 0;
				}
			}
		}
		d3[n][0][0] = 1;
		for (int i = n; i >= 1; i--) {
			for (int j = 0; i + j <= n; j++) {
				if (s[i - 1] != '(') {
					d3[i - 1][j + 1][0] += d3[i][j][0];
					if (j + 1 == h)
						d3[i - 1][j + 1][1] += d3[i][j][0];
					else if (j + 1 <= 2 * h)
						d3[i - 1][j + 1][1] += d3[i][j][1];
				}
				if (s[i - 1] != ')') {
					if (j - 1 >= 0)
						d3[i - 1][j - 1][0] += d3[i][j][0];
					if (j - 1 == h) {
						d3[i - 1][j - 1][1] += d3[i][j][0];
					} else if (j - 1 <= 2 * h && j) {
						d3[i - 1][j - 1][1] += d3[i][j][1];
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int a = 0; a < h; a++) {
				ans += d2[i][a] * d3[i][(h - a) * 2 - 1][2 * a < h];
			}
		}
	}
	for (int h = 0; h <= n; h++) {
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < 2 * MAXN; j++) {
				for (int k = 0; k < 3; k++) {
					d3[i][j][k] = 0;
				}
			}
		}

		d3[n][n][0] = 1;
		if (h + d == 0)
			d3[n][n][1] = 1;
		for (int i = n; i >= 1; i--) {
			for (int j = -(n - i); j <= (n - i); j++) {
				if (s[i - 1] != '(') {
					if (j + 1 >= 0)
						d3[i - 1][j + 1 + n][0] += d3[i][j + n][0];
					if (j + 1 == h + d) {
						d3[i - 1][j + 1 + n][1] += d3[i][j + n][0];
					} else if (j + 1 >= 0) {
						d3[i - 1][j + 1 + n][1] += d3[i][j + n][1];
					}
					if (j + 1 == -1) {
						d3[i - 1][j + 1 + n][2] += d3[i][j + n][1];
					}
					if (j + 1 <= 2 * h) {
						d3[i - 1][j + 1 + n][2] += d3[i][j + n][2];
					}
				}
				if (s[i - 1] != ')') {
					if (j - 1 >= 0)
						d3[i - 1][j - 1 + n][0] += d3[i][j + n][0];
					if (j - 1 == h + d) {
						d3[i - 1][j - 1 + n][1] += d3[i][j + n][0];
					} else if (j - 1 >= 0) {
						d3[i - 1][j - 1 + n][1] += d3[i][j + n][1];
					}
					if (j - 1 == -1) {
						d3[i - 1][j - 1 + n][2] += d3[i][j + n][1];
					}
					if (j - 1 <= 2 * h) {
						d3[i - 1][j - 1 + n][2] += d3[i][j + n][2];
					}
				}
			}
		}
		for (int a = 0; a <= n; a++) {
			int b = 2 * (a - h);
			if (b >= -n && b < n)
				for (int i = 1; i <= n; i++)
					ans += d3[i][-1 - b + n][2] * d2[i][a];
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	if (n % 2 == 1) {
		cout << "0\n";
		return 0;
	}
	mint ret = 0;
	{
		vector<mint> dp(n + 1);
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			vector<mint> nxt(n + 1);
			for (int j = 0; j < n; j++) {
				if (j && s[i] != '(')
					nxt[j - 1] += dp[j];
				if (s[i] != ')')
					nxt[j + 1] += dp[j];
			}
			dp = nxt;
		}
		ret += dp[0];
	}
	ret += f(s, 0);
	reverse(all(s));
	for (auto &x : s) {
		if (x == '(')
			x = ')';
		else if (x == ')')
			x = '(';
	}
	ret += f(s, 1);

	cout << ret << "\n";
}