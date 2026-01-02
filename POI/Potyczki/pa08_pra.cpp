#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int mod;
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
const int MAXN = 200005;

struct bit {
	mint tree[MAXN];
	void add(int x, mint v) {
		for (int i = x; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	mint query(int x) {
		mint ret = 0;
		for (int i = x; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	{
		int x, y;
		cin >> x >> y >> n >> mod;
	}
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	sort(all(a), [&](const pi &a, const pi &b) { return pi{a[0], -a[1]} < pi{b[0], -b[1]}; });
	vector<mint> dp(n);
	for (int i = 0; i < n; i++) {
		dp[i] = mint(1) + bit.query(a[i][1] - 1);
		bit.add(a[i][1], dp[i]);
	}
	cout << accumulate(all(dp), mint(1)) << "\n";
}