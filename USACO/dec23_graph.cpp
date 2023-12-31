#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int mod = 1e9 + 7;
const int MAXN = 400005;

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

mint pwr[MAXN];
struct node {
	mint sum;
	int len;
	node operator+(const node &nd) const { return (node){nd.sum + sum * pwr[nd.len], len + nd.len}; }
};

struct disj {
	int pa[MAXN];
	node lazy[MAXN], value[MAXN];
	void init(int n) {
		for (int i = 0; i < n; i++) {
			pa[i] = i;
		}
	}
	int find(int x) {
		if (pa[x] == x)
			return x;
		vector<int> seq = {x};
		while (pa[seq.back()] != seq.back()) {
			int j = pa[seq.back()];
			seq.push_back(j);
		}
		node cum = {mint(0), 0};
		for (int i = sz(seq) - 2; i >= 0; i--) {
			pa[seq[i]] = seq.back();
			lazy[seq[i]] = lazy[seq[i]] + cum;
			cum = lazy[seq[i]];
		}
		return pa[x];
	}
	void uni(int p, int q, int r) {
		p = find(p);
		q = find(q);
		pa[p] = r;
		pa[q] = r;
		assert(lazy[r].sum == mint(0));
	}
	void apply(int p, node v) {
		p = find(p);
		lazy[p] = lazy[p] + v;
		//		lazy[p] = lazy[p] + v;
	}
	node query(int x) {
		find(x);
		node ret = lazy[x];
		while (x != pa[x]) {
			x = pa[x];
			ret = ret + lazy[x];
		}
		return ret;
	}
} disj;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	pwr[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pwr[i] = pwr[i - 1] * mint(10);
	int n, m;
	cin >> n >> m;
	disj.init(n * 2);
	int c = 0;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (disj.find(u) == disj.find(v))
			continue;
		auto Q1 = disj.query(u);
		auto Q2 = disj.query(v);
		disj.apply(u, (node){mint(i), 1});
		disj.apply(v, (node){mint(i), 1});
		disj.apply(u, Q2);
		disj.apply(v, Q1);
		disj.uni(u, v, n + c);
		c++;
	}
	for (int i = 0; i < n; i++) {
		cout << disj.query(i).sum << "\n";
	}
}