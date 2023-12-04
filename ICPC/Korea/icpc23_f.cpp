#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using pi = array<int, 2>;
const int MAXT = 66000;

struct seg1 {
	int tree[MAXT];
	int lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			lazy[i] += lazy[p];
			tree[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = max(tree[2 * p], tree[2 * p + 1]);
	}
	int query(int s, int e, int ps, int pe, int p) {
		if (e < ps || pe < s)
			return 0;
		if (s <= ps && pe <= e)
			return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p);
		return max(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
	int traverse(int s, int e, int ps, int pe, int p, int c) {
		if (e < ps || pe < s)
			return 0;
		if (s <= ps && pe <= e) {
			if (tree[p] < c)
				return 0;
			if (ps == pe)
				return ps;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		int w = traverse(s, e, pm + 1, pe, 2 * p + 1, c);
		if (w != 0)
			return w;
		return traverse(s, e, ps, pm, 2 * p, c);
	}
} seg;

struct seg2 {
	int lim;
	pi tree[MAXT];
	void init(int n, vector<pi> &a) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
		fill(tree, tree + MAXT, pi{int(1e9), -1});
		for (int i = 0; i < n; i++) {
			tree[i + lim] = pi{a[i][1], i};
		}
		for (int i = lim - 1; i; i--)
			tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
	int query(int s, int e) {
		pi ret{int(1e9), -1};
		s += lim;
		e += lim;
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
		return ret[1];
	}
	void rem(int x) {
		x += lim;
		tree[x] = pi{int(1e9), -1};
		while (x > 1) {
			x >>= 1;
			tree[x] = min(tree[2 * x], tree[2 * x + 1]);
		}
	}
} seg2;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> crd;
	vector<pi> a(n);
	for (auto &[x, y] : a) {
		cin >> x >> y;
		crd.push_back(x);
		crd.push_back(y + 1);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for (auto &[x, y] : a) {
		x = lower_bound(all(crd), x) - crd.begin() + 1;
		y = lower_bound(all(crd), y + 1) - crd.begin();
	}
	int m = sz(crd);
	sort(all(a));
	seg2.init(n, a);
	int ans = 0;
	vector<int> dap(n + 1, 0);
	vector<int> pos(m + 1);
	for (auto &[x, y] : a)
		pos[x]++;
	for (int i = 1; i <= m; i++)
		pos[i] += pos[i - 1];
	dap[0] = n;
	for (int i = 1; i <= n; i++) {
		for (int p = 0; p < m;) {
			auto j = pos[p];
			auto q = seg2.query(j, n - 1);
			if (q == -1)
				break;
			seg.add(a[q][0], a[q][1], 1, m, 1, 1);
			seg2.rem(q);
			ans++;
			p = seg.traverse(1, a[q][1], 1, m, 1, i);
		}
		dap[i] = n - ans;
	}
	int s = 0, e = n;
	while (s != e) {
		int m = (s + e) / 2;
		if (dap[m] + 1ll * k * m < dap[m + 1] + 1ll * k * (m + 1))
			e = m;
		else
			s = m + 1;
	}
	cout << dap[s] + 1ll * k * s << "\n";
}