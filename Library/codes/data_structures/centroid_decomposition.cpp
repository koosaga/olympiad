#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

// idk, use global array to communicate
const int MAXN = 200005;
lint a[MAXN];

// Centroid decomposition, supporting
// 0) a[x] += y
// 1) sum_{dist(v, i) \in [l, r]} a[i] for (v, l, r)

namespace CD {
/* ---- modification starts here ---- */
const int MAXL = 18;
const int MAXN = 200005;
struct edge {
	int pos;
};
vector<edge> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];
int par[MAXN], dep[MAXN], pae[MAXN];

struct fenwick {
	vector<lint> tree;
	void init(int n) {
		tree.clear();
		tree.resize(n + 3);
	}
	void add(int x, lint v) {
		for (int i = x + 1; i < sz(tree); i += i & -i)
			tree[i] += v;
	}
	lint query(int x) {
		lint ret = 0;
		for (int i = x + 1; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
};

struct DS {
	map<int, int> subToIdx;
	vector<fenwick> fenws;
	lint query(int p, int l, int r) {
		p = subToIdx[p];
		l = max(l, 0);
		r = min(r, sz(fenws[p].tree) - 2);
		if (l <= r)
			return fenws[p].query(r) - fenws[p].query(l - 1);
		return 0;
	}
	void upd(int p, int l, int v) {
		p = subToIdx[p];
		if (l >= 0 && l < sz(fenws[p].tree) - 1) {
			fenws[p].add(l, v);
		}
	}
} assoc[MAXN];

struct shortcut {
	int dist;
} ds[MAXL][MAXN];

void dfsPopulate(int x, int p, vector<lint> &sums, int d = 1) {
	if (sz(sums) <= d)
		sums.resize(d + 1);
	sums[d] += a[x];
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfsPopulate(y.pos, x, sums, d + 1);
		}
	}
}

void fillDS(int x) {
	assoc[x].subToIdx[x] = 0;
	int cnt = 1;
	for (auto &y : gph[x]) {
		if (!vis[y.pos]) {
			assoc[x].subToIdx[y.pos] = cnt++;
		}
	}
	assoc[x].fenws.resize(cnt);
	cnt = 1;
	vector<lint> totals(1);
	totals[0] += a[x];
	for (auto &y : gph[x]) {
		if (!vis[y.pos]) {
			vector<lint> v;
			dfsPopulate(y.pos, x, v);
			assoc[x].fenws[cnt].init(sz(v));
			for (int i = 0; i < sz(v); i++)
				assoc[x].fenws[cnt].add(i, v[i]);
			cnt++;

			if (sz(totals) < sz(v))
				totals.resize(sz(v));
			for (int i = 0; i < sz(v); i++)
				totals[i] += v[i];
		}
	}
	assoc[x].fenws[0].init(sz(totals));
	for (int i = 0; i < sz(totals); i++)
		assoc[x].fenws[0].add(i, totals[i]);
}

void dfsCalcDist(int l, int x, int p = -1, int d = 0) {
	ds[l][x].dist = d;
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfsCalcDist(l, y.pos, x, d + 1);
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
		fillDS(x);
		vis[x] = 1;
		for (auto &y : gph[x]) {
			if (!vis[y.pos]) {
				que.push({y.pos, x, dep[x] + 1});
			}
		}
	}
}

/* ---- queries ---- */

void update(int x, int v) {
	int ppe = -1;
	for (int i = x; i != -1; i = par[i]) {
		int d = ds[dep[i]][x].dist;
		assoc[i].upd(i, d, v);
		if (ppe != -1)
			assoc[i].upd(ppe, d, v);
		ppe = pae[i];
	}
}

lint query(int x, int l, int r) {
	lint ret = 0;
	int ppe = -1;
	for (int i = x; i != -1; i = par[i]) {
		int d = ds[dep[i]][x].dist;
		ret += assoc[i].query(i, l - d, r - d);
		if (ppe != -1)
			ret -= assoc[i].query(ppe, l - d, r - d);
		ppe = pae[i];
	}
	return ret;
}

} // namespace CD

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		CD::addEdge(u, {v});
		CD::addEdge(v, {u});
	}
	CD::init();
	while (q--) {
		int t, v;
		cin >> t >> v;
		if (t == 0) {
			int x;
			cin >> x;
			CD::update(v, x);
		} else {
			int l, r;
			cin >> l >> r;
			cout << CD::query(v, l, r - 1) << "\n";
		}
	}
}