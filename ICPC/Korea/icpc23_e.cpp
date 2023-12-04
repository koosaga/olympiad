#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const lint mod = (lint)1e18 + 31;
const int MAXN = 1000005;
// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

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
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

const int pwr = 257;

struct bit1 {
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
} bit1;
struct bit2 {
	mint tree[MAXN];
	void add(int x, mint v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	mint query(int x) {
		mint ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit2;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k, m, n;
	cin >> k >> m >> n;
	vector<mint> P(n + 1);
	P[0] = 1;
	for (int i = 1; i <= n; i++)
		P[i] = P[i - 1] * mint(257);
	vector<vector<int>> V(m);
	map<lint, int> mp;
	for (int i = 0; i < m; i++) {
		mint H;
		V[i].resize(k);
		for (auto &x : V[i]) {
			cin >> x;
		}
		for (int j = 0; j < k; j++) {
			H += mint(bit1.query(V[i][j])) * P[j];
			bit1.add(V[i][j], +1);
		}
		for (auto &x : V[i])
			bit1.add(x, -1);
		mp[H.val] = i;
	}
	vector<int> seq(n);
	for (auto &x : seq) {
		cin >> x;
	}
	{
		auto y = seq;
		sort(all(y));
		y.resize(unique(all(y)) - y.begin());
		for (auto &p : seq)
			p = lower_bound(all(y), p) - y.begin();
	}
	mint cur = 0;
	mint cinv = 1;
	for (int i = 0; i < n; i++) {
		cur += P[i] * mint(bit1.query(seq[i]));
		bit1.add(seq[i], +1);
		bit2.add(seq[i], +P[i]);
		if (i >= k - 1) {
			mint nxt = cur * cinv;
			cinv *= 494'163'424'124'513'634ll;
			if (mp.count(nxt.val)) {
				for (auto &j : V[mp[nxt.val]])
					cout << j << " ";
				return 0;
			}
			bit1.add(seq[i - k + 1], -1);
			bit2.add(seq[i - k + 1], -P[i - k + 1]);
			cur -= (bit2.query(n) - bit2.query(seq[i - k + 1]));
		}
	}
	cout << "0\n";
}