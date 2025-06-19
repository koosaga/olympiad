#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXT = 1050000;

pi combine(pi a, pi b) {
	if (a[0] == b[0])
		return pi{a[0], a[1] + b[1]};
	if (a[1] > b[1])
		swap(a, b);
	return pi{b[0], b[1] - a[1]};
}

struct bit {
	int tree[MAXT];
	void add(int x, int v) {
		for (int i = x + 1; i < MAXT; i += i & -i) {
			tree[i] += v;
		}
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 1; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

struct seg {
	pi tree[MAXT];
	int lim;
	void init(vector<int> &a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++)
			tree[i + lim] = pi{a[i], 1};
		for (int i = lim - 1; i; i--)
			tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
	}
	void upd(int x, int v) {
		x += lim;
		tree[x] = pi{v, 1};
		while (x > 1) {
			x >>= 1;
			tree[x] = combine(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int l, int r) {
		l += lim;
		r += lim;
		pi ret{0, 0};
		while (l < r) {
			if (l % 2 == 1)
				ret = combine(ret, tree[l++]);
			if (r % 2 == 0)
				ret = combine(tree[r--], ret);
			l >>= 1;
			r >>= 1;
		}
		if (l == r)
			ret = combine(ret, tree[l]);
		return ret[0];
	}
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<pi> coords;
	for (int i = 0; i < n; i++)
		coords.push_back({a[i], i});
	vector<array<int, 3>> queries(q);
	for (int i = 0; i < q; i++) {
		for (int j = 1; j < 3; j++)
			cin >> queries[i][j];
		queries[i][0] = 1;
		queries[i][1]--;
		if (queries[i][0] == 0) {
			coords.push_back({queries[i][2], queries[i][1]});
		}
	}
	seg.init(a);
	for (auto &[x, y, z] : queries) {
		if (x == 0) {
			seg.upd(y, z);
			x = -1;
		} else {
			x = seg.query(y, z - 1);
		}
	}
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
	auto Add = [&](pi p, int v) {
		int z = lower_bound(all(coords), p) - coords.begin();
		bit.add(z + 1, v);
	};
	for (int i = 0; i < n; i++) {
		Add(pi{a[i], i}, +1);
	}
	for (int i = 0; i < q; i++) {
		if (~queries[i][0]) {
			int ll = lower_bound(all(coords), pi{queries[i][0], queries[i][1]}) - coords.begin();
			int rr = lower_bound(all(coords), pi{queries[i][0], queries[i][2]}) - coords.begin();
			int qq = bit.query(rr) - bit.query(ll);
			if (qq * 2 <= queries[i][2] - queries[i][1])
				cout << "0\n";
			else
				cout << queries[i][0] << "\n";
		} else {
			int j = queries[i][1];
			int k = queries[i][2];
			Add(pi{a[j], j}, -1);
			a[j] = k;
			Add(pi{a[j], j}, +1);
		}
	}
}