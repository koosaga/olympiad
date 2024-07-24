#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
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

pair<lint, mint> solve(lint l, vector<pi> a) {
	sort(all(a));
	int n = sz(a);
	for (int i = 0; i < n; i++) {
		a.push_back({a[i][0] + l, a[i][1]});
	}
	int cur = n;
	vector<int> idx(3 * n + 1, -1);
	vector<pi> nxt(n, pi{-1, -1});
	vector<int> indeg(n);
	for (int i = 0; i < sz(a); i++) {
		if (a[i][1] < 0) {
			int prv = idx[cur - 1];
			if (prv < n && ~prv)
				nxt[prv] = pi{i % n, a[i][0] - a[prv][0]}, indeg[i % n]++;
			idx[--cur] = i;
		} else {
			int prv = idx[cur];
			if (prv < n && ~prv)
				nxt[prv] = pi{i % n, a[i][0] - a[prv][0]}, indeg[i % n]++;
			idx[cur++] = i;
		}
	}
	lint ans = 0;
	mint cnt = 1;
	for (int i = 0; i < n; i++) {
		if (indeg[i])
			continue;
		vector<lint> sums;
		for (int j = i; nxt[j][0] != -1; j = nxt[j][0]) {
			sums.push_back(nxt[j][1]);
		}
		assert(sz(sums) % 2 == 0);
		lint cur = 0;
		for (int i = 0; i < sz(sums); i += 2)
			cur += sums[i];
		lint minval = cur;
		int minhow = 1;
		for (int i = sz(sums) - 1; i >= 0; i -= 2) {
			cur += sums[i] - sums[i - 1];
			if (minval > cur) {
				minval = cur;
				minhow = 0;
			}
			if (minval == cur)
				minhow++;
		}
		cnt *= mint(minhow);
		ans += minval;
	}
	return make_pair(ans, cnt);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n1, n2, l;
	cin >> l >> n1 >> n2;
	vector<pi> v;
	for (int i = 0; i < n1 + n2; i++) {
		lint p;
		string s;
		cin >> p >> s;
		v.push_back({p, s == "H" ? +1 : -1});
	}
	auto [a, b] = solve(l, v);
	cout << a << "\n" << b << "\n";
}