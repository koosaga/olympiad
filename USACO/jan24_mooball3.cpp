
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005;
const int MAXT = 530000;
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

mint inv[MAXN];
int a[MAXN];

struct bit {
	int tree[MAXN];
	void clear() { memset(tree, 0, sizeof(tree)); }
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

struct mtrx {
	mint a[2][2];
	mtrx() {
		for (int i = 0; i < 4; i++)
			a[i >> 1][i & 1] = 0;
	}

	mtrx operator*(const mtrx &m) {
		mtrx ret;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					ret.a[j][k] += a[j][i] * m.a[i][k];
				}
			}
		}
		return ret;
	}
};

mtrx I() {
	mtrx m;
	m.a[0][0] = m.a[1][1] = 1;
	return m;
}
mtrx SMALL() {
	mtrx m;
	m.a[0][0] = 2;
	m.a[1][1] = 1;
	return m;
}
mtrx LARGE() {
	mtrx m;
	m.a[0][0] = m.a[0][1] = 1;
	m.a[1][1] = 2;
	return m;
}
struct seg {
	mtrx tree[MAXT];
	int lim;
	void init(int n) {
		fill(tree, tree + MAXT, I());
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < n; i++)
			tree[i + lim] = LARGE();
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] * tree[2 * i + 1];
	}
	void upd(int x, mtrx v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] * tree[2 * x + 1];
		}
	}
	mtrx query(int s, int e) {
		s += lim;
		e += lim;
		mtrx L = I(), R = I();
		while (s < e) {
			if (s % 2 == 1)
				L = L * tree[s++];
			if (e % 2 == 0)
				R = tree[e--] * R;
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			L = L * tree[s];
		return L * R;
	}
} seg;

mint solve(vector<int> a) {
	int n = sz(a);
	vector<int> rev(n);
	for (int i = 0; i < n; i++)
		rev[a[i]] = i;
	mint ans = 0;
	bit.clear();
	seg.init(n);
	for (int i = 1; i < n; i++) {
		int z = rev[i - 1];
		bit.add(z, 1);
		seg.upd(z, SMALL());
		mint gobs = ipow(mint(2), bit.query(z - 1));
		ans += gobs * seg.query(z + 1, n - 1).a[0][1];
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[x - 1] = y - 1;
	}
	mint ans = 0;
	for (int i = 1; i < n; i++) {
		ans += mint(4) * ipow(mint(2), i - 1) * (ipow(mint(2), n - i) - mint(1));
	}
	ans -= mint(2) * solve(a);
	reverse(all(a));
	ans -= mint(2) * solve(a);
	cout << ans << "\n";
}