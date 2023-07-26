#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int MAXN = 1000005;
const string pat = "CIP";

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
	mint tree[MAXN];
	void add(int x, mint v) {
		for (int i = x + 3; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	mint query(int x) {
		mint ret = 0;
		for (int i = x + 3; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit[3];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// (a1 - a2 same, < a3)
	string s;
	cin >> s;
	int n = sz(s);
	vector<vector<int>> sum(3, vector<int>(n + 1));
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= n; j++) {
			sum[i][j] = sum[i][j - 1] + (s[j - 1] == pat[i]);
		}
	}
	vector<array<int, 3>> g[3];
	vector<vector<int>> rev(3, vector<int>(n + 1));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			g[j].push_back({sum[j][i] - sum[(j + 1) % 3][i], sum[(j + 2) % 3][i] - sum[(j + 1) % 3][i], i});
		}
	}
	for (int i = 0; i < 3; i++) {
		sort(all(g[i]));
		for (int j = 0; j <= n; j++)
			rev[i][g[i][j][2]] = j;
	}
	for (int i = 0; i <= n; i++) {
		mint ans = 0;
		for (int j = 0; j < 3; j++) {
			int s = lower_bound(all(g[j]), array<int, 3>{sum[j][i] - sum[(j + 1) % 3][i], -int(1e9), -1}) - g[j].begin();
			int e = lower_bound(all(g[j]), array<int, 3>{sum[j][i] - sum[(j + 1) % 3][i], sum[(j + 2) % 3][i] - sum[(j + 1) % 3][i], -int(1e9)}) - g[j].begin();
			ans += bit[j].query(e - 1) - bit[j].query(s - 1);
		}
		if (i == 0)
			ans = 1;
		if (i == n) {
			cout << ans << "\n";
		}
		for (int j = 0; j < 3; j++) {
			bit[j].add(rev[j][i], ans);
		}
	}
}