#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 1000005;
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

lint ccw(pi a, pi b, pi c) {
	lint dx1 = b[0] - a[0];
	lint dy1 = b[1] - a[1];
	lint dx2 = c[0] - a[0];
	lint dy2 = c[1] - a[1];
	return dx1 * dy2 - dy1 * dx2;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	set<pi> S;
	S.insert(pi{0, 0});
	auto cost = [&](pi p, pi q) {
		lint z = (q[1] - p[1]);
		if (z <= 0)
			return mint(0);
		lint l = (q[0] - p[0]);
		assert(l > 0);
		return ipow(mint(3), z / l) * mint(z % l) + (z < l ? mint(0) : (ipow(mint(3), z / l - 1) * mint(l - z % l)));
	};
	mint sum = 0;
	for (int i = 0; i < n; i++) {
		lint p, d;
		cin >> p >> d;
		auto X = pi{p, d};
		auto it = S.lower_bound({p, -1});
		if (it != S.end() && ccw(*prev(it), X, *it) >= 0) {
			cout << sum << "\n";
			continue;
		}
		if (it != S.end() && (*it)[0] == X[0]) {
			if (next(it) != S.end())
				sum -= cost(*it, *next(it));
			if (it != S.begin())
				sum -= cost(*prev(it), *it);
			it = S.erase(it);
		} else if (it != S.end())
			sum -= cost(*prev(it), *it);
		it--;
		while (it != S.begin()) {
			auto pt = prev(it);
			if (ccw(*pt, *it, X) >= 0) {
				sum -= cost(*pt, *it);
				it = S.erase(it);
				it--;
			} else
				break;
		}
		sum += cost(*it, X);
		it++;
		while (it != S.end()) {
			auto nt = next(it);
			if (nt != S.end() && ccw(X, *it, *nt) >= 0) {
				sum -= cost(*it, *nt);
				it = S.erase(it);
			} else
				break;
		}
		if (it != S.end())
			sum += cost(X, *it);
		S.insert(X);
		cout << sum << "\n";
	}
}