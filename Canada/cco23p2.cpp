#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int mod = 1e6 + 3; // 1e9 + 7;//993244853;
const int MAXN = 1000005;
const int MAXT = 2100000;

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

struct seg {
	int tree[MAXT], lim;
	void init(vector<int> &a) {
		memset(tree, 0x3f, sizeof(tree));
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++) {
			tree[i + lim] = a[i];
		}
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) {
		s += lim;
		e += lim;
		int ret = 1e9;
		while (s < e) {
			if (s % 2 == 1)
				ret = min(ret, tree[s++]);
			if (e % 2 == 0)
				ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = min(ret, tree[s]);
		return ret;
	}
} seg;

struct bit {
	int tree[MAXN];
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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<pi> byval;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		byval.push_back({a[i], i});
	}
	seg.init(a);
	sort(all(byval));
	mint tot = 0;
	auto sum = [&](int l, int r) { return mint(1ll * (r - l + 1) * (r + l) / 2); };
	int l = 0, r = n;
	set<int> s;
	for (int i = 0; i < sz(byval) - 1; i++) {
		s.insert(byval[i][1]);
		seg.upd(byval[i][1], 1e9);
		bit.add(byval[i][1], 1);
		if (byval[i][0] == byval[i + 1][0])
			continue;
		int C = byval[i][0];
		int D = byval[i + 1][0];
		while (l < n && a[l] <= C)
			l++;
		while (r > l && a[r - 1] <= C)
			r--;
		if (l == r)
			break;
		auto it = s.lower_bound(l);
		if (it == s.end() || *it >= r)
			continue;

		int fp = *it;
		int gp = *--s.lower_bound(r);
		if (fp == gp) {
			tot += mint(1ll * (D - C) * (seg.query(l, fp - 1) + seg.query(fp + 1, r))) + sum(C, D - 1);
			continue;
		}
		int pcnt = bit.query(r - 1) - bit.query(l - 1);
		tot += sum(C, D - 1) * mint(pcnt);
		tot += sum(C + 1, D) * mint(2 * pcnt - 2);
		tot += mint(1ll * seg.query(l, fp - 1) * (D - C));
		tot += mint(1ll * seg.query(gp + 1, r - 1) * (D - C));
		tot += mint(1ll * (D - C) * min(seg.query(fp + 1, r - 1), seg.query(l, gp - 1))) - sum(C + 1, D);
	}
	cout << tot << "\n";
}