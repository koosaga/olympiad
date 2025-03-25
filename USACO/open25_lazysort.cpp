#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
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

const int maxn = 5000005;
const int magic = 250; // threshold for sizes to run the naive algo

template <typename T> T fact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[0] = T(1);
		for (int i = 1; i < maxn; i++) {
			F[i] = F[i - 1] * T(i);
		}
		init = true;
	}
	return F[n];
}

template <typename T> T rfact(int n) {
	static T F[maxn];
	static bool init = false;
	if (!init) {
		F[maxn - 1] = T(1) / fact<T>(maxn - 1);
		for (int i = maxn - 2; i >= 0; i--) {
			F[i] = F[i + 1] * T(i + 1);
		}
		init = true;
	}
	return F[n];
}

mint binom(int a, int b) {
	if (b < 0 || a < b)
		return mint(0);
	return fact<mint>(a) * rfact<mint>(b) * rfact<mint>(a - b);
}
const int MAXN = 5000005;

mint pwr[MAXN];

mint trans(int x, int y, int j, int k) {
	// (0, 0) -> (x, y), j <- (0, 0) is not max, k <- (x, y) is not max
	mint ans = 0;
	if (j == 0 && k == 0) {
		mint b1 = (x - 1 >= 0);
		mint b2 = (y >= 0);
		for (int d = 0; d <= x - 1; d++) {
			ans += b1 * b2 * pwr[x - 1 - d] * rfact<mint>(d) * rfact<mint>(d);
			b1 *= mint(x - 1 - d);
			b2 *= mint(y - d);
		}
	}
	if (j == 0 && k == 1) {
		if (y == -1)
			return ipow(mint(2), x - 1);
		mint b1 = max(x - 1, 0);
		mint b2 = (y >= 0);
		for (int d = 0; d <= x - 2; d++) {
			ans += b1 * b2 * pwr[x - 2 - d] * rfact<mint>(d + 1) * rfact<mint>(d);
			b1 *= mint(x - 2 - d);
			b2 *= mint(y - d);
		}
	}
	if (j == 1 && k == 0) {
		mint b1 = (x - 1 >= 0);
		mint b2 = (y - 1 >= 0);
		for (int d = 0; d <= x - 1; d++) {
			ans += b1 * b2 * pwr[x - 1 - d] * rfact<mint>(d) * rfact<mint>(d);
			b1 *= mint(x - 1 - d);
			b2 *= mint(y - 1 - d);
		}
	}
	if (j == 1 && k == 1) {
		if (y == 0)
			return ipow(mint(2), x - 1);
		mint b1 = max(x - 1, 0);
		mint b2 = (y - 1 >= 0);
		for (int d = 0; d <= x - 2; d++) {
			ans += b1 * b2 * pwr[x - 2 - d] * rfact<mint>(d + 1) * rfact<mint>(d);
			b1 *= mint(x - 2 - d);
			b2 *= mint(y - 1 - d);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int m, n;
	cin >> m >> n;
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	vector<array<mint, 2>> dp(n);
	dp[0][0] = 1;
	pwr[0] = 1;
	for (int i = 1; i <= m; i++)
		pwr[i] = pwr[i - 1] * mint(2);
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j] += dp[i - 1][k] * trans(a[i][0] - a[i - 1][0], a[i][1] - a[i - 1][1], k, j);
			}
		}
	}
	cout << dp[n - 1][0] + dp[n - 1][1] << "\n";
}