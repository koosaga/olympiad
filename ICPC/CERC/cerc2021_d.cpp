#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 530000;
struct node {
	lint minv, maxv;
	lint sum, addv;
	node operator+(const node &nd) const { return (node){min(minv, nd.minv), max(maxv, nd.maxv), sum + nd.sum, 0ll}; }
} tree[MAXT];

vector<lint> a, b;

void down(int p) {
	for (int i = 2 * p; i < 2 * p + 2; i++) {
		tree[i].minv += tree[p].addv;
		tree[i].maxv += tree[p].addv;
		tree[i].addv += tree[p].addv;
	}
	tree[p].addv = 0;
	if (tree[p].minv == tree[p].maxv) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			tree[i].minv = tree[i].maxv = tree[p].minv;
			tree[i].addv = 0;
		}
	}
}

void init(int s, int e, int p) {
	if (s == e) {
		tree[p] = (node){a[s], a[s], b[s], 0ll};
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2 * p);
	init(m + 1, e, 2 * p + 1);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void gather(int s, int e, int ps, int pe, int p, vector<pi> &v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e && tree[p].maxv == tree[p].minv) {
		v.push_back({tree[p].minv, tree[p].sum});
		return;
	}
	int pm = (ps + pe) / 2;
	down(p);
	gather(s, e, ps, pm, 2 * p, v);
	gather(s, e, pm + 1, pe, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void add(int s, int e, int ps, int pe, int p, lint v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].maxv += v;
		tree[p].minv += v;
		tree[p].addv += v;
		return;
	}
	int pm = (ps + pe) / 2;
	down(p);
	add(s, e, ps, pm, 2 * p, v);
	add(s, e, pm + 1, pe, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

void upd(int s, int e, int ps, int pe, int p, lint v) {
	if (e < ps || pe < s)
		return;
	if (s <= ps && pe <= e) {
		tree[p].maxv = tree[p].minv = v;
		tree[p].addv = 0;
		return;
	}
	int pm = (ps + pe) / 2;
	down(p);
	upd(s, e, ps, pm, 2 * p, v);
	upd(s, e, pm + 1, pe, 2 * p + 1, v);
	tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	b.resize(n);
	for (auto &x : b)
		cin >> x;
	init(0, n - 1, 1);
	while (q--) {
		int t, l, r;
		cin >> t >> l >> r;
		l--;
		r--;
		lint v;
		if (t == 1) {
			cin >> v;
			add(l, r, 0, n - 1, 1, v);
		}
		if (t == 2) {
			vector<pi> cols;
			gather(l, r, 0, n - 1, 1, cols);
			sort(all(cols));
			lint total = 0;
			for (auto &[_, z] : cols)
				total += z;
			total = (total + 1) / 2;
			for (auto &[c, z] : cols) {
				total -= z;
				if (total <= 0) {
					v = c;
					break;
				}
			}
			cout << v << "\n";
			upd(l, r, 0, n - 1, 1, v);
		}
	}
}
