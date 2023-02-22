#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXL = 17;
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

struct strips {
	int nxt[MAXL][MAXL][MAXN];
	int pae[MAXL][MAXN], dep[MAXL][MAXN];
	void build(int s, int e, int d = 0) {
		if (s == e)
			return;
		int m = (s + e) / 2;
		// [s, m]
		{
			vector<int> stk = {m};
			nxt[d][0][m] = m;
			for (int i = m - 1; i >= s; i--) {
				while (sz(stk) >= 2 && pae[d][stk.back()] >= isect(i, stk.back()))
					stk.pop_back();
				nxt[d][0][i] = stk.back();
				pae[d][i] = isect(i, stk.back());
				dep[d][i] = dep[d][stk.back()] + 1;
				stk.push_back(i);
			}
		}
		{
			// [m + 1, e]
			vector<int> stk = {m + 1};
			nxt[d][0][m + 1] = m + 1;
			for (int i = m + 2; i <= e; i++) {
				while (sz(stk) >= 2 && pae[d][stk.back()] <= isect(stk.back(), i))
					stk.pop_back();
				nxt[d][0][i] = stk.back();
				pae[d][i] = isect(stk.back(), i);
				dep[d][i] = dep[d][stk.back()] + 1;
				stk.push_back(i);
			}
		}
		for (int i = 1; i < MAXL; i++) {
			for (int j = s; j <= e; j++) {
				nxt[d][i][j] = nxt[d][i - 1][nxt[d][i - 1][j]];
			}
		}
		build(s, m, d + 1);
		build(m + 1, e, d + 1);
	}
	lint query(int s, int e, int ps, int pe, int v, int d = 0) {
		if (s == e)
			return cost(s, v);
		int pm = (ps + pe) / 2;
		if (e <= pm)
			return query(s, e, ps, pm, v, d + 1);
		if (pm + 1 <= s)
			return query(s, e, pm + 1, pe, v, d + 1);
		if (dep[d][s] > 1) {
			for (int i = l2(dep[d][s] - 1); i >= 0; i--) {
				if (nxt[d][i][s] != pm && pae[d][nxt[d][i][s]] > v)
					s = nxt[d][i][s];
			}
		}
		if (dep[d][e] > 1) {
			for (int i = l2(dep[d][e] - 1); i >= 0; i--) {
				if (nxt[d][i][e] != pm + 1 && pae[d][nxt[d][i][e]] <= v)
					e = nxt[d][i][e];
			}
		}
		if (s < pm && pae[d][s] > v)
			s = nxt[d][0][s];
		if (e > pm + 1 && pae[d][e] <= v)
			e = nxt[d][0][e];
		return max(cost(s, v), cost(e, v));
	}
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