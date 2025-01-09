#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 300005;
const int mod = 1e9 + 7;
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

struct seg {
	mint tree[MAXT][2][2];
	void add(int x, array<array<mint, 2>, 2> a) {
		for (int i = x + 2; i < MAXT; i += i & -i) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					tree[i][j][k] += a[j][k];
				}
			}
		}
	}
	array<array<mint, 2>, 2> query(int x) {
		array<array<mint, 2>, 2> a = {array<mint, 2>{mint(0), mint(0)}, array<mint, 2>{mint(0), mint(0)}};
		for (int i = x + 2; i; i -= i & -i) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					a[j][k] += tree[i][j][k];
				}
			}
		}
		return a;
	}
	array<array<mint, 2>, 2> query(int l, int r) {
		auto i1 = query(r);
		auto i2 = query(l - 1);
		array<array<mint, 2>, 2> a = {array<mint, 2>{mint(0), mint(0)}, array<mint, 2>{mint(0), mint(0)}};
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				a[j][k] = i1[j][k] - i2[j][k];
			}
		}
		return a;
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> a(n + 1);
	vector<int> v = {0};
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = a[i - 1];
		a[i][0] += x;
		if (a[i][0] >= mod) {
			a[i][0] -= mod;
			a[i][1] ^= 1;
		}
		v.push_back(a[i][0]);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	vector<mint> dp(n + 1);
	dp[0] = 1;
	auto gen = [&](int x, int y, mint t) {
		array<array<mint, 2>, 2> a = {array<mint, 2>{mint(0), mint(0)}, array<mint, 2>{mint(0), mint(0)}};
		a[x][y] = t;
		return a;
	};
	seg.add(0, gen(0, 0, mint(1)));
	for (int i = 1; i <= n; i++) {
		int pos = lower_bound(all(v), a[i][0]) - v.begin();
		auto sum1 = seg.query(0, pos);
		auto sum2 = seg.query(pos + 1, sz(v) - 1);
		dp[i] = sum1[a[i][1]][a[i][0] % 2] + sum1[a[i][1] ^ 1][(a[i][0]) % 2] + sum2[a[i][1]][(a[i][0] + 1) % 2] + sum2[a[i][1] ^ 1][(a[i][0] + 1) % 2];
		seg.add(pos, gen(a[i][1], a[i][0] % 2, dp[i]));
		//	cout << dp[i] << endl;
	}
	cout << dp[n] << "\n";
}