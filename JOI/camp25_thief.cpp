#include "thief.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 10005;

int n, m;
vector<pi> gph[MAXN];
vector<int> dfn;
int sz[MAXN], msz[MAXN];
int par[MAXN], pae[MAXN];

struct edge {
	int u, v, w;
};

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			par[y] = x;
			pae[y] = w;
			dfs(y, x);
			sz[x] += sz[y];
			msz[x] = max(msz[x], sz[y]);
		}
	}
}

int get_center(int x) {
	dfn.clear();
	dfs(x);
	pi ret{int(1e9), -1};
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		ret = min(ret, pi{w, x});
	}
	return ret[1];
}

void gather(int x, int p, vector<edge> &edges, vector<int> &P0, vector<int> &P1) {
	if (pae[x] >= 0) {
		P0[pae[x]] = 1;
		P1[pae[x]] = 0;
	} else {
		P0[~pae[x]] = 0;
		P1[~pae[x]] = 1;
	}
	edges.push_back({p, x, pae[x]});
	for (auto &[w, y] : gph[x]) {
		if (y != p)
			gather(y, x, edges, P0, P1);
	}
}

vector<vector<int>> rec(vector<edge> edges) {
	if (sz(edges) == 1) {
		vector<vector<int>> P(2);
		cr(P[0], m);
		cr(P[1], m);
		fill(all(P[0]), -1);
		fill(all(P[1]), -1);
		if (edges[0].w >= 0) {
			P[0][edges[0].w] = 0;
			P[1][edges[0].w] = 1;
		} else {
			P[0][~edges[0].w] = 0;
			P[1][~edges[0].w] = 1;
		}
		return P;
	}
	vector<int> vtx;
	for (auto &e : edges) {
		vtx.push_back(e.u);
		vtx.push_back(e.v);
		gph[e.u].push_back({e.w, e.v});
		gph[e.v].push_back({~e.w, e.u});
	}
	sort(all(vtx));
	vtx.resize(unique(all(vtx)) - vtx.begin());
	int c = get_center(vtx[0]);
	dfn.clear();
	dfs(c);
	sort(all(gph[c]), [&](const pi &a, const pi &b) { return sz[a[1]] > sz[b[1]]; });
	int hap = sz[c] - 1, cur = 0;
	pi ans{int(1e9), -1};
	for (int i = 0; i < sz(gph[c]) - 1; i++) {
		cur += sz[gph[c][i][1]];
		ans = min(ans, pi{max(cur, hap - cur), i + 1});
	}
	vector<edge> E[2];
	vector<int> P[2];
	cr(P[0], m);
	cr(P[1], m);
	fill(all(P[0]), -1);
	fill(all(P[1]), -1);
	for (int j = 0; j < ans[1]; j++) {
		gather(gph[c][j][1], c, E[0], P[0], P[1]);
	}
	for (int j = ans[1]; j < sz(gph[c]); j++) {
		gather(gph[c][j][1], c, E[1], P[1], P[0]);
	}
	for (auto &e : edges) {
		gph[e.u].clear();
		gph[e.v].clear();
	}
	auto a1 = rec(E[0]);
	auto a2 = rec(E[1]);
	vector<vector<int>> ret;
	ret.push_back(P[0]);
	ret.push_back(P[1]);
	for (int i = 0; i < max(sz(a1), sz(a2)); i++) {
		vector<int> vect(m, -1);
		for (int j = 0; j < m; j++) {
			if (i < sz(a1))
				vect[j] = max(vect[j], a1[i][j]);
			if (i < sz(a2))
				vect[j] = max(vect[j], a2[i][j]);
		}
		ret.push_back(vect);
	}
	return ret;
}

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
		pa[q] = p;
		return 1;
	}
} disj;
void solve(int N, int M, std::vector<int> U, std::vector<int> V) {
	n = N;
	m = M;
	disj.init(n);
	vector<edge> gg;
	for (int i = 0; i < m; i++) {
		if (disj.uni(U[i], V[i])) {
			gg.push_back({U[i], V[i], i});
		}
	}
	auto ans = rec(gg);
	for (int i = 0; i < sz(ans); i++) {
		vector<vector<int>> gph(n);
		vector<int> indeg(n);
		for (auto &e : gg) {
			int l = e.u, r = e.v;
			if (ans[i][e.w] == +1)
				swap(l, r);
			gph[l].push_back(r);
			indeg[r]++;
		}
		queue<int> que;
		for (int i = 0; i < n; i++) {
			if (!indeg[i]) {
				que.push(i);
			}
		}
		int piv = 0;
		vector<int> ord(n);
		while (sz(que)) {
			int x = que.front();
			que.pop();
			ord[x] = piv++;
			for (auto &y : gph[x]) {
				indeg[y]--;
				if (!indeg[y])
					que.push(y);
			}
		}
		for (int j = 0; j < m; j++) {
			ans[i][j] = max(ans[i][j], 0);
		}
		auto ask = [&](int l, int r) {
			vector<int> ans(m);
			for (int i = 0; i < m; i++) {
				int s = ord[U[i]];
				int e = ord[V[i]];
				int val = (s > e);
				if (!(l <= min(s, e) && max(s, e) <= r))
					val ^= 1;
				ans[i] = val;
			}
			return query(ans);
		};
		if (ask(0, n - 1)) {
			int s = 0, e = n - 1;
			while (s != e) {
				int m = (s + e + 1) / 2;
				if (ask(m, n - 1))
					s = m;
				else
					e = m - 1;
			}
			int l = s, r = n - 1;
			while (l != r) {
				int m = (l + r) / 2;
				if (ask(s, m))
					r = m;
				else
					l = m + 1;
			}
			int x = find(all(ord), s) - ord.begin();
			int y = find(all(ord), l) - ord.begin();
			answer(x, y);
			return;
		}
	}
}
