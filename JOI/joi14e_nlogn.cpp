#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct seg {
	int s, e, x;
	bool operator<(const seg &s) const { return x < s.x; }
};

struct sweep {
	int idx, pos, val;
	bool operator<(const sweep &s) const { return pi(idx, val) < pi(s.idx, s.val); }
};

int xsz, ysz;
vector<seg> xs, ys;

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		// cout << "uni " << p << " " << q << endl;
		pa[q] = p;
		return 1;
	}
} dsu;

const int MAXT = 530000;

struct segt {
	int tree[MAXT], lazy[MAXT], lval[MAXT];
	void init() {
		memset(tree, 0, sizeof(tree));
		memset(lazy, -1, sizeof(lazy));
		memset(lval, -1, sizeof(lval));
	}
	void App(int p, int v) {
		assert(v != -1);
		if (tree[p] == 0)
			return;
		if (~lazy[p]) {
			dsu.uni(v, lazy[p]);
		}
		lazy[p] = v;
		if (~lval[p]) {
			dsu.uni(v, lval[p]);
		}
	}
	void lazydown(int p) {
		if (~lazy[p]) {
			for (int i = 2 * p; i < 2 * p + 2; i++) {
				App(i, lazy[p]);
			}
			lazy[p] = -1;
		}
	}
	void upd(int pos, int s, int e, int p, int v) {
		if (s == e) {
			tree[p] = (v != -1);
			lval[p] = v;
			lazy[p] = -1;
			// cout << "set " << pos << " " << v << endl;
			return;
		}
		lazydown(p);
		int m = (s + e) / 2;
		if (pos <= m)
			upd(pos, s, m, 2 * p, v);
		else
			upd(pos, m + 1, e, 2 * p + 1, v);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
	int merge(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return 0;
		if (s <= ps && pe <= e) {
			//	cout << "merge " << ps << " " << pe << " " << v << endl;
			App(p, v);
			return tree[p];
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		return merge(s, e, ps, pm, 2 * p, v) + merge(s, e, pm + 1, pe, 2 * p + 1, v);
	}
} segt;
vector<array<int, 4>> norm(vector<array<int, 4>> a) {
	sort(all(a));
	vector<array<int, 4>> ans;
	for (int i = 0; i < sz(a);) {
		int j = i;
		while (j < sz(a) && a[j][0] == a[i][0])
			j++;
		int cmax = -1, last = i;
		for (int k = i; k + 1 < j; k++) {
			cmax = max(cmax, a[k][2]);
			if (cmax <= a[k + 1][1]) {
				ans.push_back({a[last][0], a[last][1], cmax, a[last][3]});
				last = k + 1;
			} else
				dsu.uni(a[k][3], a[k + 1][3]);
		}
		cmax = max(cmax, a[j - 1][2]);
		ans.push_back({a[last][0], a[last][1], cmax, a[last][3]});
		i = j;
	}
	return ans;
}

int solve_line_segment(vector<array<int, 4>> xseg, vector<array<int, 4>> yseg) {
	int w = 205000, h = 205000;
	vector<vector<array<int, 3>>> ev_line(w + 1);
	vector<vector<array<int, 2>>> ev_inst(w + 1), ev_dele(w + 1);
	for (auto &[p, l, r, i] : xseg)
		ev_line[p].push_back({l, r, i});
	for (auto &[p, l, r, i] : yseg) {
		ev_inst[l].push_back({p, i});
		ev_dele[r].push_back({p, i});
	}
	segt.init();
	for (int i = 0; i <= w; i++) {
		for (auto &[pos, idx] : ev_dele[i]) {
			segt.upd(pos, 0, h + 1, 1, -1);
		}
		for (auto &[pos, idx] : ev_inst[i]) {
			segt.upd(pos, 0, h + 1, 1, idx);
		}
		for (auto &[l, r, idx] : ev_line[i]) {
			segt.merge(l, r - 1, 0, h + 1, 1, idx);
		}
	}
	int ans = 0;
	for (int i = 0; i < sz(dsu.pa); i++) {
		if (dsu.uni(i, 0))
			ans++;
	}
	return ans + 1;
}

struct bit {
	int tree[200050];
	void add(int x, int v) {
		while (x <= xsz) {
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x) {
		int ret = 0;
		while (x) {
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
} bit;

lint get_intersection() {
	vector<sweep> swp;
	for (auto &i : xs) {
		swp.push_back({i.s, i.x, 1});
		swp.push_back({i.e + 1, i.x, -1});
	}
	sort(swp.begin(), swp.end());
	lint ret = 0;
	int p = 0;
	for (auto &j : ys) {
		while (p < swp.size() && swp[p].idx <= j.x) {
			bit.add(swp[p].pos, swp[p].val);
			p++;
		}
		ret += bit.query(j.e) - bit.query(j.s - 1);
	}
	return ret;
}

int get_component() {
	dsu.init(sz(xs) + sz(ys));
	vector<array<int, 4>> xseg, yseg;
	for (int i = 0; i < sz(xs); i++)
		xseg.push_back({xs[i].x, xs[i].s, xs[i].e + 1, i});
	for (int i = 0; i < sz(ys); i++)
		yseg.push_back({ys[i].x, ys[i].s, ys[i].e + 1, i + sz(xs)});
	return solve_line_segment(norm(xseg), norm(yseg));
}
int main() {
	vector<int> vx, vy;
	int w, h, n;
	scanf("%d %d %d", &w, &h, &n);
	vx.push_back(0);
	vx.push_back(w);
	vy.push_back(0);
	vy.push_back(h);
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		vx.push_back(x1);
		vx.push_back(x2);
		vy.push_back(y1);
		vy.push_back(y2);
		if (x1 < x2) {
			ys.push_back({x1, x2, y1});
		}
		if (y1 < y2) {
			xs.push_back({y1, y2, x1});
		}
	}
	xs.push_back({0, h, 0});
	xs.push_back({0, h, w});
	ys.push_back({0, w, 0});
	ys.push_back({0, w, h});
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for (auto &i : xs) {
		int l = lower_bound(vy.begin(), vy.end(), i.s) - vy.begin();
		int r = upper_bound(vy.begin(), vy.end(), i.e) - vy.begin() - 1;
		int x = lower_bound(vx.begin(), vx.end(), i.x) - vx.begin();
		i = {l + 1, r + 1, x + 1};
	}
	for (auto &i : ys) {
		int l = lower_bound(vx.begin(), vx.end(), i.s) - vx.begin();
		int r = upper_bound(vx.begin(), vx.end(), i.e) - vx.begin() - 1;
		int x = lower_bound(vy.begin(), vy.end(), i.x) - vy.begin();
		i = {l + 1, r + 1, x + 1};
	}
	xsz = vx.size();
	ysz = vy.size();
	cout << get_intersection() + get_component() - (n + 4) << endl;
}
