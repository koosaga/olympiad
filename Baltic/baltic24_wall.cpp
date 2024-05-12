#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXT = 1050000;
const int mod = 1e9 + 7;

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

mint pwr[MAXT];

struct node {
	int sum, len;
	mint lef, rig, prod;
	node operator+(const node &nd) const {
		if (sum == -1)
			return nd;
		if (nd.sum == -1)
			return *this;
		node ret;
		ret.sum = sum + nd.sum;
		ret.len = len + nd.len;
		ret.lef = lef * pwr[nd.len] + prod * nd.lef;
		ret.rig = nd.rig * pwr[len] + nd.prod * rig;
		ret.prod = prod * nd.prod;
		return ret;
	}
	node() {
		sum = -1;
		lef = rig = prod = 0;
	}
	node(int x) {
		sum = x;
		len = 1;
		lef = rig = prod = x;
	}
};

struct seg {
	node tree[MAXT];
	int lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		for (int i = 0; i < n; i++)
			tree[i + lim] = node(0);
		for (int i = lim - 1; i; i--)
			tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = node(v);
		while (x > 1) {
			x >>= 1;
			tree[x] = tree[2 * x] + tree[2 * x + 1];
		}
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	pwr[0] = 1;
	for (int i = 1; i < MAXT; i++)
		pwr[i] = pwr[i - 1] * mint(2);
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x;
	for (auto &[x, y] : a)
		cin >> y;
	vector<pi> events;
	for (int i = 0; i < n; i++) {
		if (a[i][0] > a[i][1])
			swap(a[i][0], a[i][1]);
		events.push_back({a[i][0], i});
		events.push_back({a[i][1], i});
	}
	int prv = 0;
	sort(all(events));
	mint ans = 0;
	seg.init(n);
	vector<int> cnt(n);
	auto solve = [&]() {
		auto qr = seg.tree[1];
		mint ans = mint(qr.sum) * pwr[n - 1] + qr.prod * mint(n) - qr.lef - qr.rig;
		return ans;
	};
	for (int i = 0; i < sz(events);) {
		int j = i;
		while (j < sz(events) && events[i][0] == events[j][0])
			j++;
		ans += mint(events[i][0] - prv) * solve();
		for (int k = i; k < j; k++) {
			cnt[events[k][1]]++;
			seg.upd(events[k][1], cnt[events[k][1]]);
		}
		prv = events[i][0];
		i = j;
	}
	cout << ans << "\n";
}