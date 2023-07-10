#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int mod = 1e9 + 7;
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

struct disj {
	mint prob[MAXN];
	int cur_time[MAXN], pa[MAXN];
	void init(int n) {
		iota(pa, pa + n + 1, 0);
		fill(cur_time, cur_time + n + 1, -1);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q, int t) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		prob[p] += mint(t - cur_time[p]);
		prob[q] += mint(t - cur_time[q]);
		prob[p] *= prob[q];
		cur_time[p] = t;
		return 1;
	}
} disj;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<array<int, 3>> edges;
	auto get = [&](int x, int y) { return x * m + y; };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m - 1; j++) {
			int x;
			cin >> x;
			edges.push_back({x, get(i, j), get(i, j + 1)});
		}
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			edges.push_back({x, get(i, j), get(i + 1, j)});
		}
	}
	sort(all(edges));
	disj.init(n * m);
	for (auto &[w, u, v] : edges) {
		disj.uni(u, v, w);
	}
	int rt = disj.find(0);
	cout << mint(k - disj.cur_time[rt]) + disj.prob[rt] << "\n";
}