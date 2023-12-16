#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 998244353;

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
map<int, lint> mp;

lint f(int n, vector<int> &trs) {
	if (n == 0)
		return 1;
	if (mp.count(n))
		return mp[n];
	lint ans = 0;
	for (auto &y : trs) {
		if ((n >= y && (n - y) % 2 == 0))
			ans += f((n - y) / 2, trs);
	}
	return mp[n] = ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;
		vector<int> a(m);
		for (auto &x : a)
			cin >> x;
		vector<int> trs;
		for (int i = 0; i < (1 << m); i++) {
			int sum = 0;
			for (int j = 0; j < m; j++) {
				if ((i >> j) & 1)
					sum += a[j];
			}
			trs.push_back(sum);
		}
		mp.clear();
		cout << f(n, trs) << "\n";
	}
}