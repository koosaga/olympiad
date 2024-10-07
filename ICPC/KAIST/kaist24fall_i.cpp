#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

const int mod = 998244353; // 1e9 + 7;//993244853;

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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<array<mint, 6>> a(n);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++) {
			mint sum = 0;
			for (int k = 3 * i; k < 3 * i + 3; k++) {
				cin >> a[j][k].val;
				sum += a[j][k];
			}
			sum = mint(1) / sum;
			for (int k = 3 * i; k < 3 * i + 3; k++) {
				a[j][k] *= sum;
			}
		}
	}
	vector<mint> D(3);
	D[0] = 1;
	mint ret = 0;
	for (int i = 0; i < n; i++) {
		vector<mint> E(3);
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				mint letithappen = a[i][j] * a[i][k + 3];
				for (int l = 0; l < 3; l++) {
					if ((j + 1) % 3 == k) {
						E[1] += letithappen * D[l];
					} else if ((j + 2) % 3 == k) {
						E[2] += letithappen * D[l];
					} else {
						if (l == 0) {
							E[0] += letithappen * D[l];
						} else {
							if (l == 1)
								ret += letithappen * D[l];
						}
					}
				}
			}
		}
		D = E;
	}
	cout << ret << "\n";
}