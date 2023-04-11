#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

// Centroid decomposition, supporting
// 0) a[x] += y
// 1) sum_{dist(v, i) \in [l, r]} a[i] for (v, l, r)

namespace CD {
/* ---- modification starts here ---- */
const int MAXL = 17;
const int MAXN = 100005;
struct edge {
	int pos, len;
};
vector<edge> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];
int par[MAXN], dep[MAXN], pae[MAXN];

struct DS {
	vector<pi> lines;
	bool bad(pi a, pi b, pi c) { return (__int128)(b[1] - a[1]) * (b[0] - c[0]) >= (__int128)(c[1] - b[1]) * (a[0] - b[0]); }
	lint query(lint x) {
		if (sz(lines) == 0)
			return 5e18;
		int s = 0, e = sz(lines) - 1;
		while (s != e) {
			int m = (s + e) / 2;
			if ((__int128)lines[m][0] * x + lines[m][1] > (__int128)lines[m + 1][0] * x + lines[m + 1][1])
				s = m + 1;
			else
				e = m;
		}
		return lines[s][0] * x + lines[s][1];
	}
	void add(lint x, lint y) {
		if (sz(lines) && lines.back()[0] == x) {
			if (lines.back()[1] > y) {
				lines.pop_back();
			} else
				return;
		}
		while (sz(lines) >= 2 && bad(lines[sz(lines) - 2], lines.back(), {x, y})) {
			lines.pop_back();
		}
		lines.push_back({x, y});
	}
} assoc[MAXN];

struct shortcut {
	lint dist;
} ds[MAXL][MAXN];

void dfsCalcDist(int l, int x, int p = -1, lint d = 0) {
	ds[l][x].dist = d;
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfsCalcDist(l, y.pos, x, d + y.len);
		}
	}
}

void fillShortcut(int x) { dfsCalcDist(dep[x], x); }

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
		fillShortcut(x);
		//	fillDS(x);
		vis[x] = 1;
		for (auto &y : gph[x]) {
			if (!vis[y.pos]) {
				que.push({y.pos, x, dep[x] + 1});
			}
		}
	}
}

/* ---- queries ---- */

void update(int x, lint A, lint B) {
	for (int i = x; i != -1; i = par[i]) {
		lint d = ds[dep[i]][x].dist;
		assoc[i].add(B, A + d * B);
	}
}

lint query(int x) {
	lint ret = 5e18;
	for (int i = x; i != -1; i = par[i]) {
		lint d = ds[dep[i]][x].dist;
		ret = min(ret, assoc[i].query(d));
	}
	return ret;
}

} // namespace CD

vector<pi> gph[MAXN];
lint dp[MAXN];

void dfs(int x, int p, lint A, lint B) {
	dp[x] = A;
	for (auto &[w, y] : gph[x]) {
		if (y != p)
			dfs(y, x, A + w * B, B);
	}
}
vector<long long> travel(vector<long long> A, vector<int> B, vector<int> U, vector<int> V, vector<int> W) {
	int n = A.size();
	for (int i = 0; i < n - 1; i++) {
		CD::addEdge(U[i], {V[i], W[i]});
		CD::addEdge(V[i], {U[i], W[i]});
		gph[U[i]].push_back({W[i], V[i]});
		gph[V[i]].push_back({W[i], U[i]});
	}
	CD::init();
	dfs(0, -1, A[0], B[0]);
	vector<int> ord;
	for (int i = 0; i < n; i++) {
		if (B[i] < B[0])
			ord.push_back(i);
	}
	sort(all(ord), [&](int a, int b) { return B[a] > B[b]; });
	for (auto &x : ord) {
		dp[x] = min(dp[x], CD::query(x));
		CD::update(x, dp[x] + A[x], B[x]);
	}
	vector<lint> ret(n - 1);
	for (int x = 0; x < n - 1; x++)
		ret[x] = min(dp[x + 1], CD::query(x + 1));
	return ret;
}
