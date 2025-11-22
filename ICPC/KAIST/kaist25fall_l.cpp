#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 530000;
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
	int d, n;
	cin >> d >> n;
	vector<array<int, 3>> v, dx;
	for (int i = 0; i < n; i++) {
		int l, r, c;
		cin >> l >> r >> c;
		l--;
		if (l > 0) {
			v.push_back({l, c, 0});
		}
		if (r < d) {
			v.push_back({r, c, 1});
		}
		dx.push_back({l + 1, +1, c});
		dx.push_back({r, -1, c});
	}
	sort(all(v));
	sort(all(dx));
	int stab = 0, p = 0;
	mint ans = 1;
	map<int, int> count;
	for (int i = 0; i < sz(v);) {
		while (p < sz(dx) && dx[p][0] <= v[i][0]) {
			count[dx[p][2]] += dx[p][1];
			stab += dx[p++][1];
		}
		int j = i;
		while (j < sz(v) && v[j][0] == v[i][0])
			j++;
		ans += mint(j - i) / mint(j - i + stab);
		map<int, pi> mp;
		pi s = {0, 0};
		for (int k = i; k < j; k++) {
			mp[v[k][1]][v[k][2]]++;
			s[v[k][2]]++;
		}
		for (auto &[k, arr] : mp) {
			if (arr[0] == 0 || arr[1] == 0)
				continue;
			mint p = mint(1ll * arr[0] * arr[1]) / mint(s[0] + s[1] + stab);
			ans -= p * (mint(s[0] + stab).inv() + mint(s[1] + stab).inv());
		}
		for (auto &[k, arr] : mp) {
			for (int j = 0; j < 2; j++) {
				int p = stab - count[k] + s[0] + s[1] - arr[j];
				int q = count[k];
				int r = arr[j];
				ans -= mint(1ll * q * r) / mint(1ll * (stab + s[0] + s[1] - s[j]) * (stab + s[0] + s[1]));
			}
		}
		i = j;
	}
	cout << ans << "\n";
}