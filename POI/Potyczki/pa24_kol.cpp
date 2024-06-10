

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;
const int MAXT = 530000;

vector<array<lint, 3>> query; // (vert, dist, attr)

struct query_t {
	int s, e, u, v;
	lint d;
};

struct router_t {
	int v[2];
	lint d[2];
};

struct node {
	vector<int> vset;
	vector<router_t> route;		  // (merged dp, pdp, comp because of mle)
	vector<array<lint, 3>> trees; // trees finalized for the range, given as input
	vector<lint> maxDist;		  // for vertex in vset, max (rad - dist)
} tree[MAXT];

vector<pi> gph[MAXN];
bool vis[MAXN], chk[MAXN];
int par[MAXN];
pi dp[MAXN], pdp[MAXN];

pi dfs(int x, int p, vector<array<lint, 3>> &edges) { // has stuff, how dist
	vector<pi> lows;
	vis[x] = 1;
	dp[x] = pi{lint(1e18), 0};
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			par[y] = x;
			auto lo = dfs(y, x, edges);
			if (lo[1] < lint(1e17))
				lows.push_back(pi{lo[0], lo[1] + w});
			dp[x] = min(dp[x], pi{dp[y][0] + w, dp[y][1]});
		}
	}
	if (chk[x] || sz(lows) > 1) {
		chk[x] = 1;
		for (auto &[v, w] : lows) {
			edges.push_back({x, v, w});
		}
		dp[x] = pi{0, x};
		lows.clear();
		lows.push_back({x, 0});
	}
	if (sz(lows) == 0)
		return pi{0, lint(1e18)};
	if (sz(lows) == 1)
		return lows[0];
	assert(0);
}

void rdfs(int x, int p) {
	if (chk[x])
		pdp[x] = pi{0, x};
	vector<array<lint, 3>> v;
	for (auto &[w, y] : gph[x]) {
		if (y == p)
			continue;
		auto chs = array<lint, 3>{dp[y][0] + w, dp[y][1], y};
		v.push_back(chs);
	}
	sort(all(v));
	reverse(all(v));
	if (sz(v) > 2)
		v.resize(2);
	vis[x] = 0;
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			pdp[y] = min(pdp[y], pi{pdp[x][0] + w, pdp[x][1]});
			for (auto &[d, f, yy] : v) {
				if (yy != y)
					pdp[y] = min(pdp[y], pi{d + w, f});
			}
			rdfs(y, x);
		}
	}
}

lint val[MAXN];
pi comp[MAXN];

void dfs2(int x, int p) {
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			dfs2(y, x);
			val[x] = max(val[x], val[y] - w);
		}
	}
}

void rdfs2(int x, int p) {
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			val[y] = max(val[y], val[x] - w);
			rdfs2(y, x);
		}
	}
}

void dfs3(int x, int p, int c) {
	for (auto &[w, y] : gph[x]) {
		if (y != p && comp[y][0] == -1) {
			comp[y][0] = c;
			comp[y][1] = comp[x][1] + w;
			dfs3(y, x, c);
		}
	}
}
int mapping[MAXN];

void solve(int s, int e, int p, vector<query_t> queries) {
	// we compress the given tree
	vector<int> newVset;
	vector<array<lint, 3>> newTrees;
	{
		for (auto &[u, v, w] : tree[p].trees) {
			gph[u].push_back({w, v});
			gph[v].push_back({w, u});
		}
		for (auto &x : queries) {
			chk[x.u] = 1;
			chk[x.v] = 1;
		}
		for (int i = s; i < e; i++)
			chk[query[i][0]] = 1;
		for (auto &v : tree[p].vset) {
			if (!vis[v]) {
				dfs(v, -1, newTrees);
			}
		}
		for (auto &v : tree[p].vset) {
			pdp[v] = pi{lint(1e18), 0};
			if (chk[v])
				comp[v] = {v, 0};
			else
				comp[v] = pi{-1, -1};
		}
		for (auto &v : tree[p].vset) {
			if (vis[v]) {
				rdfs(v, -1);
			}
		}
		for (auto &[v, u, w] : newTrees) {
			for (int j = u; j != v; j = par[j])
				comp[j] = {j, 0};
		}
		for (auto &v : tree[p].vset) {
			if (~comp[v][0])
				dfs3(v, -1, comp[v][0]);
		}
		for (auto &v : tree[p].vset) {
			if (chk[v]) {
				newVset.push_back(v);
			}
			if (comp[v][0] == -1) {
				tree[p].route.push_back({{-1, -1}, {0, 0}});
			} else {
				int w = comp[v][0];
				lint d = comp[v][1];
				tree[p].route.push_back({{(int)dp[w][1], (int)pdp[w][1]}, {dp[w][0] + d, pdp[w][0] + d}});
			}
		}
		for (auto &v : tree[p].vset) {
			vis[v] = chk[v] = 0;
			dp[v] = pdp[v] = pi{lint(1e18), 0};
			comp[v] = {-1, -1};
			gph[v].clear();
		}
	}
	vector<lint> cmax;
	if (s + 1 == e) {
		assert(sz(queries) == 0);
		assert(sz(newTrees) == 0);
		assert(sz(newVset) == 1);
		assert(newVset[0] == query[s][0]);
		cmax.push_back(query[s][1]);
	} else {
		int m = (s + e) / 2;
		tree[2 * p].vset = tree[2 * p + 1].vset = newVset;
		tree[2 * p].trees = tree[2 * p + 1].trees = newTrees;
		vector<query_t> left, right;
		for (auto &[l, r, u, v, w] : queries) {
			if (l <= s && m <= r) {
				tree[2 * p].trees.push_back({u, v, w});
			} else if (l < m) {
				left.push_back({l, r, u, v, w});
			}
			if (l <= m && e <= r) {
				tree[2 * p + 1].trees.push_back({u, v, w});
			} else if (r > m) {
				right.push_back({l, r, u, v, w});
			}
		}
		solve(s, m, 2 * p, left);
		solve(m, e, 2 * p + 1, right);
		assert(sz(tree[2 * p].maxDist) == sz(newVset));
		assert(sz(tree[2 * p + 1].maxDist) == sz(newVset));
		cmax.resize(sz(newVset));
		for (int i = 0; i < sz(newVset); i++) {
			cmax[i] = max(tree[2 * p].maxDist[i], tree[2 * p + 1].maxDist[i]);
		}
	}
	for (int i = 0; i < sz(newVset); i++) {
		mapping[newVset[i]] = i;
	}
	for (auto &x : tree[p].vset)
		val[x] = -1e18;
	for (int i = 0; i < sz(tree[p].vset); i++) {
		if (~mapping[tree[p].vset[i]]) {
			val[tree[p].vset[i]] = cmax[mapping[tree[p].vset[i]]];
		} else {
			for (int t = 0; t < 2; t++) {
				if (tree[p].route[i].v[t] == -1 || tree[p].route[i].d[t] > 1e17)
					continue;
				val[tree[p].vset[i]] = max(val[tree[p].vset[i]], cmax[mapping[tree[p].route[i].v[t]]] - tree[p].route[i].d[t]);
			}
		}
	}
	for (int i = 0; i < sz(newVset); i++) {
		mapping[newVset[i]] = -1;
	}
	for (auto &[u, v, w] : tree[p].trees) {
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
	}
	for (auto &v : tree[p].vset) {
		if (!vis[v]) {
			dfs2(v, -1);
			rdfs2(v, -1);
		}
	}
	for (auto &v : tree[p].vset) {
		tree[p].maxDist.push_back(val[v]);
		vis[v] = 0;
		gph[v].clear();
	}
}

int query_f(int s, int e, int ps, int pe, int p, map<lint, lint> v) {
	if (e <= ps || pe <= s)
		return 0;
	if (s <= ps && pe <= e) {
		bool ok = 0;
		//	cout << "queries at node " << p << endl;
		for (auto &[x, t] : v) {
			//		cout << x << " " << t << endl;
			int l = lower_bound(all(tree[p].vset), x) - tree[p].vset.begin();
			assert(l < sz(tree[p].vset) && tree[p].vset[l] == x);
			if (tree[p].maxDist[l] >= t)
				ok = 1;
		}
		if (!ok)
			return 0;
		else if (pe - ps == 1)
			return pe;
	}
	int pm = (ps + pe) / 2;
	map<lint, lint> lows;
	for (auto &[x, d] : v) {
		int i = lower_bound(all(tree[p].vset), x) - tree[p].vset.begin();
		assert(i < sz(tree[p].vset) && tree[p].vset[i] == x);
		for (int t = 0; t < 2; t++) {
			if (tree[p].route[i].v[t] == -1 || tree[p].route[i].d[t] > 1e17)
				continue;
			lint nv = tree[p].route[i].v[t];
			lint nw = d + tree[p].route[i].d[t];
			if (lows.count(nv))
				lows[nv] = min(lows[nv], nw);
			else
				lows[nv] = nw;
		}
	}
	//	cout << "at node " << p << endl;
	//	for (auto &[k, v] : lows)
	//		cout << k << " " << v << endl;
	int q = query_f(s, e, pm, pe, 2 * p + 1, lows);
	if (q > 0)
		return q;
	return query_f(s, e, ps, pm, 2 * p, lows);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	map<pi, pi> edges;
	vector<query_t> intervals;
	for (int i = 0; i < m; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		u--;
		v--;
		if (u > v)
			swap(u, v);
		edges[pi{u, v}] = pi{0, d};
	}
	vector<pi> fours;
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			int u, v, d;
			cin >> u >> v >> d;
			u--;
			v--;
			if (u > v)
				swap(u, v);
			edges[pi{u, v}] = pi{sz(query), d};
		}
		if (t == 2) {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			if (u > v)
				swap(u, v);
			auto g = edges[pi{u, v}];
			edges.erase(pi{u, v});
			if (g[0] < sz(query)) {
				intervals.push_back({(int)g[0], sz(query), u, v, g[1]});
			}
		}
		if (t == 3) {
			int u;
			lint z, k;
			cin >> u >> z >> k;
			u--;
			query.push_back({u, z, k});
		}
		if (t == 4) {
			int u;
			cin >> u;
			fours.push_back({u - 1, sz(query)});
		}
	}
	for (auto &[k, g] : edges) {
		if (g[0] < sz(query)) {
			intervals.push_back({(int)g[0], sz(query), (int)k[0], (int)k[1], g[1]});
		}
	}
	tree[1].vset.resize(n);
	iota(all(tree[1].vset), 0);
	vector<query_t> queries;
	for (auto &[l, r, s, e, x] : intervals) {
		if (l == 0 && r == sz(query)) {
			tree[1].trees.push_back({s, e, x});
		} else
			queries.push_back({l, r, s, e, x});
	}
	memset(mapping, -1, sizeof(mapping));
	solve(0, sz(query), 1, queries);
	for (auto &[v, l] : fours) {
		map<lint, lint> s;
		s[v] = 0;
		int d = query_f(0, l, 0, sz(query), 1, s);
		cout << (d == 0 ? 0 : query[d - 1][2]) << "\n";
	}
}