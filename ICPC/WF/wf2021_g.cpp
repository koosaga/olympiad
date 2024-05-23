#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.
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

using real_t = double;
using base = complex<real_t>;

void fft(vector<base> &a, bool inv) {
	int n = a.size(), j = 0;
	vector<base> roots(n / 2);
	for (int i = 1; i < n; i++) {
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}
	real_t ang = 2 * acos(real_t(-1)) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++) {
		roots[i] = base(cos(ang * i), sin(ang * i));
	}
	/*
	   XOR Convolution : set roots[*] = 1.
	   OR Convolution  : It's easy, don't try to use FFT. https://codeforces.com/blog/entry/115438
	 */
	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv)
		for (int i = 0; i < n; i++)
			a[i] /= n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n1, m1, n2, m2;
	cin >> n1 >> m1;
	vector<vector<vector<base>>> A(3, vector<vector<base>>(2048, vector<base>(2048)));
	vector<vector<vector<base>>> B(3, vector<vector<base>>(2048, vector<base>(2048)));
	for (int i = n1 - 1; i >= 0; i--) {
		for (int j = m1 - 1; j >= 0; j--) {
			int x;
			cin >> x;
			A[0][i][j] = x;
			A[1][i][j] = x * x;
			A[2][i][j] = x * x * x;
		}
	}
	cin >> n2 >> m2;
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < m2; j++) {
			int x;
			cin >> x;
			B[2][i][j] = x;
			B[1][i][j] = x * x;
			B[0][i][j] = x * x * x;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2048; j++) {
			fft(A[i][j], false);
			fft(B[i][j], false);
		}
		for (int j = 0; j < 2048; j++) {
			vector<base> aa, bb;
			for (int k = 0; k < 2048; k++) {
				aa.push_back(A[i][k][j]);
				bb.push_back(B[i][k][j]);
			}
			fft(aa, false);
			fft(bb, false);
			vector<base> cc(2048);
			for (int k = 0; k < 2048; k++)
				cc[k] = aa[k] * bb[k];
			fft(cc, true);
			for (int k = 0; k < 2048; k++) {
				A[i][k][j] = cc[k];
			}
		}
		for (int j = 0; j < 2048; j++) {
			fft(A[i][j], true);
		}
	}
	vector<pi> dap;
	for (int i = n1 - 1; i < n2; i++) {
		for (int j = m1 - 1; j < m2; j++) {
			if ((lint)round(A[0][i][j].real()) + (lint)round(A[2][i][j].real()) == 2 * (lint)round(A[1][i][j].real())) {
				dap.push_back({i - (n1 - 2), j - (m1 - 2)});
			}
		}
	}
	cout << sz(dap) << "\n";
	for (auto &x : dap)
		cout << x[0] << " " << x[1] << "\n";
}