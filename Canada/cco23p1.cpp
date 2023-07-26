#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int mod = 1e6 + 3; // 1e9 + 7;//993244853;

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

mint bino(int n, int k) {
	mint up = 1, dn = 1;
	for (int i = 0; i < k; i++) {
		up *= mint(n - i);
		dn *= mint(i + 1);
	}
	return up / dn;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n - k + 1);
	for (int i = 0; i < n - k + 1; i++)
		cin >> a[i];
	vector<int> d(n);
	for (int i = 0; i + k < n; i++) {
		d[i + k] = d[i] + a[i + 1] - a[i];
	}
	int free = 0;
	for (int i = 0; i < k; i++) {
		int lo = 1e9;
		for (int j = i; j < n; j += k) {
			lo = min(lo, d[j]);
		}
		int hi = 0;
		for (int j = i; j < n; j += k) {
			d[j] -= lo;
			hi = max(d[j], hi);
		}
		if (hi >= 2) {
			cout << "0\n";
			return 0;
		}
		if (hi == 0) {
			free++;
		}
	}
	int ks = a[0] - accumulate(d.begin(), d.begin() + k, 0);
	if (ks < 0 || ks > free) {
		cout << "0\n";
		return 0;
	}
	cout << bino(free, ks) << "\n";
}