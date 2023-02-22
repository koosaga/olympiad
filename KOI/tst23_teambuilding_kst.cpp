#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXT = 132000;

vector<pi> l, r;

lint cost(int a, int b) { return (l[a][0] + r[b][0]) * (l[a][1] + r[b][1]); }
int l2(int x) { return 31 - __builtin_clz(x); }

int isect(int u, int v) {
	assert(u < v);
	// # of indices (prefix) where v is better than u
	int s = 0, e = sz(r);
	while (s != e) {
		int m = (s + e) / 2;
		if (cost(u, m) < cost(v, m))
			s = m + 1;
		else
			e = m;
	}
	return s;
}

int isect2(int u, int v) {
	assert(u < v);
	// # of indices (prefix) where v is better than u
	int s = 0, e = sz(l);
	while (s != e) {
		int m = (s + e) / 2;
		if (cost(m, u) < cost(m, v))
			s = m + 1;
		else
			e = m;
	}
	return s;
}

struct seg {
	lint tree[MAXT];
	int lim = (1 << 16);
	void upd(int x, lint v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	lint query(int s, int e) {
		s += lim;
		e += lim;
		lint ret = 0;
		while (s < e) {
			if (s % 2 == 1)
				ret = max(ret, tree[s++]);
			if (e % 2 == 0)
				ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = max(ret, tree[s]);
		return ret;
	}
} seg;

const int inf = 1e9;
struct line {
	int idx;
	lint eval(int v) { return cost(idx, v); }
	// returns the x-intercept of intersection "strictly" larger than T
	// in case of same: smaller index wins
	int cross_after(line &x, lint T) {
		int incep = isect(min(idx, x.idx), max(idx, x.idx));
		if (incep > T)
			return incep;
		return inf;
	}
};

struct node {
	line val;
	int melt;
	int l, r;
};

node tree[15571557]; // we only have O(n log^2 n) upper bound for this size.
int piv;

int newnode() { return ++piv; }

bool cmp(line &a, line &b, int T) {
	lint l = a.eval(T), r = b.eval(T);
	if (l != r)
		return l < r;
	return a.idx > b.idx;
}

void pull(int p, int T) {
	int L = tree[p].l;
	int R = tree[p].r;
	tree[p].val = cmp(tree[L].val, tree[R].val, T) ? tree[R].val : tree[L].val;
	tree[p].melt = min({tree[L].melt, tree[R].melt, tree[L].val.cross_after(tree[R].val, T)});
}

void init(int s, int e, int p) {
	if (s == e) {
		tree[p] = {(line){s}, inf, 0, 0};
		return;
	}
	int m = (s + e) / 2;
	tree[p].l = newnode();
	tree[p].r = newnode();
	init(s, m, tree[p].l);
	init(m + 1, e, tree[p].r);
	pull(p, 0);
}

lint query(int s, int e, int ps, int pe, int p, int T) {
	if (e < ps || pe < s)
		return 0;
	if (s <= ps && pe <= e)
		return tree[p].val.eval(T);
	int pm = (ps + pe) / 2;
	return max(query(s, e, ps, pm, tree[p].l, T), query(s, e, pm + 1, pe, tree[p].r, T));
}

void heaten(int s, int e, int p1, int p2, int T) {
	tree[p2] = tree[p1];
	if (tree[p2].melt > T)
		return;
	int m = (s + e) / 2;
	tree[p2] = tree[p1];
	tree[p2].l = newnode();
	tree[p2].r = newnode();
	heaten(s, m, tree[p1].l, tree[p2].l, T);
	heaten(m + 1, e, tree[p1].r, tree[p2].r, T);
	pull(p2, T);
}

struct strips {
	vector<int> roots;
	void build(int s, int e) {
		roots.resize(sz(r));
		roots[0] = newnode();
		init(s, e, roots[0]);
		for (int i = 1; i < sz(r); i++) {
			roots[i] = newnode();
			heaten(s, e, roots[i - 1], roots[i], i);
		}
	}
	lint query(int s, int e, int ps, int pe, int v) { return ::query(s, e, ps, pe, roots[v], v); }
} strips;

struct queries {
	int l1, r1, l2, r2, idx;
};

vector<lint> ans;
vector<queries> conts[MAXN];

void solve(vector<queries> q, int s, int e) {
	if (sz(q) == 0)
		return;
	if (s == e) {
		for (auto &z : q)
			ans[z.idx] = strips.query(z.l1, z.r1, 0, sz(l) - 1, s);
		return;
	}
	int m = (s + e) / 2;
	vector<queries> sl, sr, mid;
	for (auto &z : q) {
		if (z.r2 <= m)
			sl.push_back(z);
		else if (z.l2 >= m + 1)
			sr.push_back(z);
		else
			mid.push_back(z);
	}
	solve(sl, s, m);
	solve(sr, m + 1, e);
	auto Q = [&](int u, int v, int i) {
		if (u > v)
			return 0ll;
		return strips.query(u, v, 0, sz(l) - 1, i);
	};
	// [s, m]
	{
		for (auto &z : mid)
			conts[z.l2].push_back(z);
		for (auto &z : conts[m])
			ans[z.idx] = max(ans[z.idx], Q(z.l1, z.r1, m));
		vector<array<lint, 3>> stk; // (cur, insec, optimals from cur)
		stk.push_back({m, 0, Q(0, sz(l) - 1, m)});
		seg.upd(sz(stk) - 1, stk.back()[2]);
		auto trace = [&](int p) { // min m with stk[m][1] > p (m > 0 always hold)
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (stk[m][1] > p)
					e = m;
				else
					s = m + 1;
			}
			return s;
		};
		int msz = 1;
		for (int i = m - 1; i >= s; i--) {
			while (sz(stk) >= 2 && stk.back()[1] >= isect2(i, stk.back()[0])) {
				stk.pop_back();
			}
			int is = isect2(i, stk.back()[0]);
			stk.back()[2] = Q(stk.back()[1], is - 1, stk.back()[0]);
			seg.upd(sz(stk) - 1, stk.back()[2]);
			stk.push_back({i, is, Q(is, sz(l) - 1, i)});
			seg.upd(sz(stk) - 1, stk.back()[2]);
			msz = max(msz, sz(stk));
			for (auto &z : conts[i]) {
				int p1 = trace(z.l1) - 1; // where z.l1 at
				int p2 = trace(z.r1) - 1; // where z.r1 at
				if (p1 == p2) {
					ans[z.idx] = max(ans[z.idx], Q(z.l1, z.r1, stk[p1][0]));
					continue;
				}
				ans[z.idx] = max({ans[z.idx], Q(z.l1, stk[p1 + 1][1] - 1, stk[p1][0]), Q(stk[p2][1], z.r1, stk[p2][0])});
				ans[z.idx] = max(ans[z.idx], seg.query(p1 + 1, p2 - 1));
			}
		}
		for (auto &z : mid)
			conts[z.l2].clear();
		for (int i = 0; i < msz; i++)
			seg.upd(i, 0);
	}
	// [m+1, e]
	{
		for (auto &z : mid)
			conts[z.r2].push_back(z);
		for (auto &z : conts[m + 1])
			ans[z.idx] = max(ans[z.idx], Q(z.l1, z.r1, m + 1));
		vector<array<lint, 3>> stk; // (cur, insec, optimals from cur)
		stk.push_back({m + 1, sz(l), Q(0, sz(l) - 1, m + 1)});
		seg.upd(sz(stk) - 1, stk.back()[2]);
		auto trace = [&](int p) { // min m with stk[m][1] <= p (m > 0 always hold)
			int s = 0, e = sz(stk);
			while (s != e) {
				int m = (s + e) / 2;
				if (stk[m][1] <= p)
					e = m;
				else
					s = m + 1;
			}
			return s;
		};
		int msz = 1;
		for (int i = m + 2; i <= e; i++) {
			while (sz(stk) >= 2 && stk.back()[1] <= isect2(stk.back()[0], i)) {
				stk.pop_back();
			}
			int is = isect2(stk.back()[0], i);
			stk.back()[2] = Q(is, stk.back()[1] - 1, stk.back()[0]);
			seg.upd(sz(stk) - 1, stk.back()[2]);
			stk.push_back({i, is, Q(0, is - 1, i)});
			seg.upd(sz(stk) - 1, stk.back()[2]);
			msz = max(msz, sz(stk));
			for (auto &z : conts[i]) {
				int p1 = trace(z.l1) - 1; // where z.l1 at
				int p2 = trace(z.r1) - 1; // where z.r1 at (p1 >= p2)
				if (p1 == p2) {
					ans[z.idx] = max(ans[z.idx], Q(z.l1, z.r1, stk[p1][0]));
					continue;
				}
				ans[z.idx] = max({ans[z.idx], Q(z.l1, stk[p1][1] - 1, stk[p1][0]), Q(stk[p2 + 1][1], z.r1, stk[p2][0])});
				ans[z.idx] = max(ans[z.idx], seg.query(p2 + 1, p1 - 1));
			}
		}
		for (auto &z : mid)
			conts[z.r2].clear();
		for (int i = 0; i < msz; i++)
			seg.upd(i, 0);
	}
}

vector<long long> build_teams(vector<int> A1, vector<int> B1, vector<int> A2, vector<int> B2, vector<int> L1, vector<int> R1, vector<int> L2, vector<int> R2) {
	l.resize(sz(A1));
	r.resize(sz(A2));
	for (int i = 0; i < sz(A1); i++)
		l[i] = {A1[i], B1[i]};
	for (int i = 0; i < sz(A2); i++)
		r[i] = {A2[i], B2[i]};
	strips.build(0, sz(l) - 1);
	ans.resize(sz(L1));
	vector<queries> v;
	for (int i = 0; i < sz(L1); i++) {
		v.push_back({L1[i], R1[i], L2[i], R2[i], i});
	}
	solve(v, 0, sz(r) - 1);
	return ans;
}
