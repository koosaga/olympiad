#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

// https://judge.yosupo.jp/submission/23481
//  p need to be prime.
//  find solution to x^k == a mod p

lint mod;

struct mint {
	lint val;
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
		val = (__int128)val * m.val % mod;
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

lint mul(lint x, lint y, lint mod) { return (__int128)x * y % mod; }

lint ipow(lint x, lint y, lint p) {
	lint ret = 1, piv = x % p;
	while (y) {
		if (y & 1)
			ret = mul(ret, piv, p);
		piv = mul(piv, piv, p);
		y >>= 1;
	}
	return ret;
}

lint kth_root(lint a, lint k, lint p) {
	mod = p;
	a %= p;
	if (k == 0)
		return a == 1 ? a : -1;
	if (a <= 1 || k <= 1)
		return a;

	assert(p > 2);
	lint g = gcd(p - 1, k);
	if (ipow(mint(a), (p - 1) / g) != mint(1))
		return -1;
	return 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint p, e;
	cin >> p >> e;
	int tc;
	cin >> tc;
	while (tc--) {
		lint a;
		cin >> a;
		cout << (kth_root(a, e, p) < 0 ? "NIE" : "TAK") << "\n";
	}
}