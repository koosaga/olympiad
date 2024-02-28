#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

// idk
const int MAXL = 17;
const int MAXN = 100005;

vector<int> C;
vector<vector<pi>> gph;
int piv, n, m;

void dijk_addEdge(int u, int v, int w) {
	if (sz(gph) < max(u, v) + 1) {
		gph.resize(max(u, v) + 1);
	}
	gph[u].push_back({w, v});
}

namespace CD {
/* ---- modification starts here ---- */

struct edge {
	int pos;
};
vector<edge> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];
int par[MAXN], dep[MAXN], pae[MAXN];

struct DS {
	int cur_dis = 0;
	int piv = 0;
	int getIn(int d) { return piv - 2 * cur_dis + 2 * d; }
	int getOut(int d) { return piv - 2 * cur_dis + 2 * d + 1; }
} assoc[MAXN];

struct shortcut {
	int dist;
} ds[MAXL][MAXN];

void dfsPopulate(int x, int p, int src, int d) {
	ds[dep[src]][x].dist = d;
	if (assoc[src].cur_dis <= d) {
		assoc[src].piv += 2;
		assoc[src].cur_dis++;
		if (d > 0) {
			dijk_addEdge(assoc[src].getIn(d), assoc[src].getIn(d - 1), 0);
			dijk_addEdge(assoc[src].getOut(d - 1), assoc[src].getOut(d), 0);
		}
	}
	dijk_addEdge(assoc[src].getIn(d), x + m, 0);
	dijk_addEdge(x + m, x + n + m, C[x]);
	dijk_addEdge(x + n + m, assoc[src].getOut(d), 0);
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfsPopulate(y.pos, x, src, d + 1);
		}
	}
}

void fillDS(int x) {
	assoc[x].piv = piv;
	assoc[x].cur_dis = 0;
	dfsPopulate(x, -1, x, 0);
	piv = assoc[x].piv;
}

/* ---- modification ends here (hopefully) ---- */

void addEdge(int v, edge e) { gph[v].push_back(e); }

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfs(y.pos, x);
			sz[x] += sz[y.pos];
			msz[x] = max(msz[x], sz[y.pos]);
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

void init() {
	queue<array<int, 3>> que;
	que.push({0, -1, 0});
	while (sz(que)) {
		auto [x, p, d] = que.front();
		que.pop();
		{
			int px = x;
			x = get_center(x);
			pae[x] = px;
		}
		par[x] = p;
		dep[x] = d;
		fillDS(x);
		vis[x] = 1;
		for (auto &y : gph[x]) {
			if (!vis[y.pos]) {
				que.push({y.pos, x, dep[x] + 1});
			}
		}
	}
}

void query(int x, int r, int p) {
	for (int i = x; i != -1; i = par[i]) {
		int d = ds[dep[i]][x].dist;
		if (d <= r) {
			int w = min(r - d, assoc[i].cur_dis - 1);
			dijk_addEdge(p, assoc[i].getIn(w), 0);
			dijk_addEdge(assoc[i].getOut(w), p, 0);
		}
	}
}
} // namespace CD

vector<long long> find_spread(int N, int M, vector<int> A, vector<int> B, vector<int> P, vector<int> D, vector<int> _C) {
	C = _C;
	m = M;
	n = N;
	piv = N + M + N;
	gph.resize(piv);
	for (int i = 0; i < N - 1; i++) {
		CD::addEdge(A[i], {B[i]});
		CD::addEdge(B[i], {A[i]});
	}
	CD::init();
	for (int i = 0; i < M; i++) {
		CD::query(P[i], D[i], i);
	}
	vector<lint> dist(sz(gph), 1e18);
	using node = pair<lint, int>;
	queue<int> que;
	priority_queue<node, vector<node>, greater<node>> pq;
	dist[0] = 0;
	que.push(0);
	while (sz(pq) || sz(que)) {
		int x;
		if (sz(que)) {
			x = que.front();
			que.pop();
		} else {
			auto [D, X] = pq.top();
			pq.pop();
			if (D != dist[X])
				continue;
			x = X;
		}
		for (auto &[w, y] : gph[x]) {
			if (dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				if (w == 0)
					que.push(y);
				else
					pq.push({dist[y], y});
			}
		}
	}
	dist.resize(M);
	for (auto &x : dist)
		if (x > 1e17)
			x = -1;
	return dist;
}
