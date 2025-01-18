#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

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

const int MAXT = 2100000;

struct seg {
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
	void merge(int s, int e, int ps, int pe, int p, int v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			//	cout << "merge " << ps << " " << pe << " " << v << endl;
			App(p, v);
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		merge(s, e, ps, pm, 2 * p, v);
		merge(s, e, pm + 1, pe, 2 * p + 1, v);
	}
} seg;

void solve_line_segment(vector<array<int, 4>> xseg, vector<array<int, 4>> yseg, int w, int h) {
	vector<vector<array<int, 3>>> ev_line(w + 1);
	vector<vector<array<int, 2>>> ev_inst(w + 1), ev_dele(w + 1);
	for (auto &[p, l, r, i] : xseg)
		ev_line[p].push_back({l, r, i});
	for (auto &[p, l, r, i] : yseg) {
		ev_inst[l].push_back({p, i});
		ev_dele[r].push_back({p, i});
	}
	seg.init();
	for (int i = 0; i <= w; i++) {
		for (auto &[pos, idx] : ev_dele[i]) {
			seg.upd(pos, 0, h + 1, 1, -1);
		}
		for (auto &[pos, idx] : ev_inst[i]) {
			seg.upd(pos, 0, h + 1, 1, idx);
		}
		for (auto &[l, r, idx] : ev_line[i]) {
			seg.merge(l, r - 1, 0, h + 1, 1, idx);
		}
	}
}
struct rtree {
	vector<pi> tree[MAXT];
	vector<int> delta[MAXT];
	int lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1)
			;
	}
	void upd(int p, pi v) {
		for (int i = p + lim; i; i >>= 1) {
			tree[i].push_back(v);
		}
	}
	void preprep() {
		for (int i = 0; i < MAXT; i++) {
			if (sz(tree[i])) {
				delta[i].resize(sz(tree[i]));
			}
		}
	}
	void go(int p, int l, int r, int idx) {
		l = lower_bound(all(tree[p]), pi{l, -1}) - tree[p].begin();
		r = lower_bound(all(tree[p]), pi{r, -1}) - tree[p].begin();
		if (l == r)
			return;
		delta[p][l]++;
		delta[p][r - 1]--;
		dsu.uni(idx, tree[p][l][1]);
	}
	void apply(int s, int e, int l, int r, int p) {
		s += lim;
		e += lim;
		while (s < e) {
			if (s % 2 == 1)
				go(s++, l, r, p);
			if (e % 2 == 0)
				go(e--, l, r, p);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			go(s, l, r, p);
	}
	void postprep() {
		for (int i = 0; i < MAXT; i++) {
			if (sz(tree[i])) {
				int cur = 0;
				for (int j = 0; j + 1 < sz(tree[i]); j++) {
					cur += delta[i][j];
					if (cur)
						dsu.uni(tree[i][j][1], tree[i][j + 1][1]);
				}
			}
		}
	}
} rtree;

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

vector<int> find_union(int N, vector<int> A, vector<int> B, vector<int> C, vector<int> D) {
	vector<int> vx, vy;
	for (auto &x : A)
		vx.push_back(x);
	for (auto &x : B)
		vy.push_back(x);
	for (auto &x : C)
		vx.push_back(x + 1);
	for (auto &x : D)
		vy.push_back(x + 1);
	sort(all(vx));
	vx.resize(unique(all(vx)) - vx.begin());
	sort(all(vy));
	vy.resize(unique(all(vy)) - vy.begin());
	for (auto &x : A)
		x = lower_bound(all(vx), x) - vx.begin();
	for (auto &x : B)
		x = lower_bound(all(vy), x) - vy.begin();
	for (auto &x : C)
		x = lower_bound(all(vx), x + 1) - vx.begin();
	for (auto &x : D)
		x = lower_bound(all(vy), x + 1) - vy.begin();

	dsu.init(N);
	// line segment case
	{
		vector<array<int, 4>> xseg, yseg;
		for (int i = 0; i < N; i++) {
			xseg.push_back({A[i], B[i], D[i], i});
			yseg.push_back({B[i], A[i], C[i], i});
		}
		solve_line_segment(norm(xseg), norm(yseg), sz(vx), sz(vy));
	}
	// points case
	{
		vector<array<int, 3>> points;
		for (int i = 0; i < N; i++) {
			points.push_back({A[i], B[i], i});
			if (B[i] + 1 < D[i])
				points.push_back({A[i], D[i] - 1, i});
			if (A[i] + 1 < C[i]) {
				points.push_back({C[i] - 1, B[i], i});
				if (B[i] + 1 < D[i])
					points.push_back({C[i] - 1, D[i] - 1, i});
			}
		}
		sort(all(points), [&](array<int, 3> &a, array<int, 3> &b) { return pi{a[1], a[2]} < pi{b[1], b[2]}; });
		rtree.init(sz(vx));
		for (int i = 0; i < sz(points); i++) {
			rtree.upd(points[i][0], {points[i][1], points[i][2]});
		}
		rtree.preprep();
		for (int i = 0; i < N; i++) {
			rtree.apply(A[i], C[i] - 1, B[i], D[i], i);
		}
		rtree.postprep();
	}
	// return answer
	vector<int> ans(N, -1);
	int ptr = 0;
	for (int i = 0; i < N; i++) {
		if (ans[dsu.find(i)] == -1) {
			ans[dsu.find(i)] = ptr++;
		}
		ans[i] = ans[dsu.find(i)];
	}
	return ans;
}
