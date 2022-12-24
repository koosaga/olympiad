#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 50005;
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

int dp[MAXN][2][3];
int a[MAXN][3], n;

int f(int pos, int mode, int val) {
	if (pos == n - 1)
		return (val == 1);
	if (~dp[pos][mode][val])
		return dp[pos][mode][val];
	int ret = -1e9;
	for (int j = 0; j < 3; j++) {
		if (!mode && a[pos][val] >= a[pos + 1][j])
			continue;
		if (mode && a[pos][val] <= a[pos + 1][j])
			continue;
		ret = max(ret, f(pos + 1, mode ^ 1, j));
	}
	if (val == 1)
		ret++;
	return dp[pos][mode][val] = ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i][1];
		a[i][0] = -1e9;
		a[i][2] = 1e9;
	}
	memset(dp, -1, sizeof(dp));
	int ret = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			ret = max(ret, f(0, i, j));
		}
	}
	cout << n - ret << "\n";
}