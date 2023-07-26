#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 270000;

pi operator+(pi a, pi b) {
	if (a > b)
		swap(a, b);
	if (b[0] == a[0])
		b[1] += a[1];
	return b;
}

struct seg {
	pi tree[MAXT];
	int lazy[MAXT];
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			lazy[i] += lazy[p];
			tree[i][0] += lazy[p];
		}
		lazy[p] = 0;
	}
	void init(int s, int e, int p) {
		lazy[p] = 0;
		if (s == e) {
			tree[p] = {0, 1};
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p);
		init(m + 1, e, 2 * p + 1);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	void upd(int pos, int ps, int pe, int p, pi v) {
		if (ps == pe) {
			tree[p] = v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		if (pos <= pm)
			upd(pos, ps, pm, 2 * p, v);
		else
			upd(pos, pm + 1, pe, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	void add(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			lazy[p] += v;
			tree[p][0] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	pi query() { return tree[1]; }
} seg;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k, q;
	cin >> n >> k >> q;
	vector<int> a1(n), a2(n);
	vector<int> r1(n), r2(n);
	for (int i = 0; i < n; i++) {
		cin >> a1[i];
		a1[i]--;
		r1[a1[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> a2[i];
		a2[i]--;
		r2[a2[i]] = i;
	}
	vector<vector<array<int, 3>>> swp(n + 1);
	vector<vector<array<int, 4>>> temp(n + 1);
	vector<pi> queries(q + 1);
	for (int i = 0; i < n; i++) {
		int x1 = max(k - 1, r1[i]), x2 = min(r1[i] + k, n);
		int y1 = max(k - 1, r2[i]), y2 = min(r2[i] + k, n);
		swp[x1].push_back({y1, y2, +1});
		swp[x2].push_back({y1, y2, -1});
	}
	auto rangeAdd = [&](int p, int l, int r, int d, int ts) {
		if (p < k - 1 || p >= n)
			return;
		l = max(l, k - 1);
		r = min(r, n);
		temp[p].push_back({ts, l, r, d});
	};
	for (int i = 1; i <= q; i++) {
		int t;
		cin >> t;
		t--;
		int p1 = a1[t], p2 = a1[t + 1];
		swap(a1[t], a1[t + 1]);
		rangeAdd(r1[p1], r2[p1], r2[p1] + k, -1, i);
		rangeAdd(r1[p1] + k, r2[p1], r2[p1] + k, +1, i);
		rangeAdd(r1[p2] + k - 1, r2[p2], r2[p2] + k, -1, i);
		rangeAdd(r1[p2] - 1, r2[p2], r2[p2] + k, +1, i);
		r1[p1]++;
		r1[p2]--;
	}
	seg.init(k - 1, n - 1, 1);
	auto rangeAdd2 = [&](int l, int r, int d) { seg.add(l, r - 1, k - 1, n - 1, 1, d); };
	auto query = [&]() { return seg.tree[1]; };
	vector<vector<array<lint, 3>>> haha(q + 1);
	for (int i = k - 1; i < n; i++) {
		for (auto &x : swp[i]) {
			rangeAdd2(x[0], x[1], x[2]);
		}
		temp[i].push_back({q + 1, 0, 0});
		int las = 0;
		for (auto &[ts, l, r, d] : temp[i]) {
			auto [mx, mxc] = query();
			haha[las].push_back({i, mx, mxc});
			las = ts;
			rangeAdd2(l, r, d);
		}
		for (auto &[ts, l, r, d] : temp[i]) {
			rangeAdd2(l, r, -d);
		}
	}
	seg.init(k - 1, n - 1, 1);
	for (int i = 0; i <= q; i++) {
		for (auto [j, mx, mxc] : haha[i]) {
			seg.upd(j, k - 1, n - 1, 1, pi{mx, mxc});
		}
		queries[i] = seg.query();
		if (queries[i][0] == 0)
			queries[i][1] = 1ll * (n - k + 1) * (n - k + 1);
		cout << queries[i][0] << " " << queries[i][1] << "\n";
	}
}
