#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005;
const int mod = 998244353; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// Polynomial composition is due to ecnerwala:
// https://judge.yosupo.jp/submission/336262
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

int f[MAXN];
mint dp[MAXN][20];

const int maxn = 1 << 19;
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

mint binom(int u, int v) {
	if (v < 0 || u < v)
		return mint(0);
	return fact<mint>(u) * rfact<mint>(v) * rfact<mint>(u - v);
}

const int roots[20] = {33586463,  41597132,	 121740068, 235625759, 241438339, 275253410, 279584389,
					   358387700, 379736824, 483792241, 543954958, 570317395, 570806865, 625930627,
					   648582808, 671805320, 751761297, 776544969, 818134997, 933205338};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = n - 2; i >= 0; i--)
		a[i] = min(a[i], a[i + 1]);
	for (int i = 1; i <= 200000; i++) {
		f[i] = lower_bound(all(a), i) - a.begin();
	}
	vector<vector<int>> divs(MAXN);
	for (int i = 1; i < MAXN; i++) {
		for (int j = 2 * i; j < MAXN; j += i)
			divs[j].push_back(i);
	}
	mint ans = 0;
	for (int i = 1; i <= 200000; i++) {
		dp[i][0] += mint(f[i] == 0);
		for (auto &j : divs[i]) {
			int l = max(f[j], f[i] - 1);
			for (int z = 0; z < 19; z++) {
				dp[i][z + 1] += dp[j][z];
				dp[i][0] -= dp[j][z] * binom(l, z + 1);
			}
		}
		for (int z = 0; z < 19; z++)
			ans += dp[i][z] * binom(n - 1, z);
	}
	cout << ans << "\n";
}