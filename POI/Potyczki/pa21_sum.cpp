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
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0];
		a[i][1] = i;
	}
	sort(all(a));
	vector<lint> sum(n + 1);
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i] + a[i][0];
	}
	string ans(n, 'N');
	vector<int> prec(n);
	for (int i = 0; i < n; i++) {
		prec[i] = lower_bound(all(a), pi{sum[i], -1}) - a.begin();
	}
	for (int i = 0; i < n; i++) {
		lint cur = a[i][0];
		int pos = lower_bound(all(a), pi{a[i][0], -1}) - a.begin();
		cur += sum[pos];
		if (pos == 0)
			continue;
		int npos = lower_bound(all(a), pi{cur, -1}) - a.begin();
		if (npos == pos)
			continue;
		pos = npos;
		cur = sum[pos];
		ans[a[i][1]] = 'T';
		while (pos < n) {
			int it = prec[pos];
			if (pos < it) {
				cur = sum[it];
				pos = it;
			} else {
				ans[a[i][1]] = 'N';
				break;
			}
		}
	}
	cout << ans << "\n";
}