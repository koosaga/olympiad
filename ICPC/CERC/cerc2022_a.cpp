#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using line = array<lint, 3>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()

int n;

namespace CD {
/* ---- modification starts here ---- */
const int MAXL = 18;
const int MAXN = 200005;
struct edge {
	int pos;
	lint len, rlen;
};
vector<edge> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];
int par[MAXN], dep[MAXN], pae[MAXN];

struct fenwick {
	vector<lint> tree;
	vector<lint> coords;
	void packCoords(lint v) { coords.push_back(v); }
	void init() {
		sort(all(coords));
		coords.resize(unique(all(coords)) - coords.begin());
		tree.resize(sz(coords) + 3);
	}

	void add(lint v) {
		v = upper_bound(all(coords), v) - coords.begin();
		for (int i = v; i; i -= i & -i)
			tree[i] += 1;
	}
	lint query(lint x) {
		lint ret = 0;
		x = lower_bound(all(coords), x) - coords.begin() + 1;
		for (int i = x; i < sz(tree); i += i & -i)
			ret += tree[i];
		return ret;
	}
};

struct DS {
	map<int, int> subToIdx;
	vector<fenwick> fenws;
	lint query(int p, lint v) {
		p = subToIdx[p];
		if (v >= 0) {
			return fenws[p].query(v);
		}
		return 0;
	}
	void upd(int p, lint v) {
		p = subToIdx[p];
		if (v >= 0) {
			fenws[p].add(v);
		}
	}
} assoc[MAXN];

struct shortcut {
	lint dist;
} ds[MAXL][MAXN];

// (cent node, what subproblem, in which distance)
vector<array<lint, 3>> idxToFenwick[MAXN];

void dfsPopulate(int x, int pa, lint d, vector<array<lint, 2>> &storage) {
	if (x >= n)
		storage.push_back({x, d});
	for (auto &y : gph[x]) {
		if (!vis[y.pos] && y.pos != pa) {
			dfsPopulate(y.pos, x, d + y.len, storage);
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
	if (x >= n) {
		idxToFenwick[x].push_back({x, x, 0});
		assoc[x].fenws[0].packCoords(0);
	}
	cnt = 1;
	for (auto &y : gph[x]) {
		if (!vis[y.pos]) {
			vector<array<lint, 2>> v;
			dfsPopulate(y.pos, x, y.len, v);
			for (auto &[eidx, len] : v) {
				idxToFenwick[eidx].push_back({x, y.pos, len});
				idxToFenwick[eidx].push_back({x, x, len});
				assoc[x].fenws[0].packCoords(len);
				assoc[x].fenws[cnt].packCoords(len);
			}
			cnt++;
		}
	}
	for (auto &z : assoc[x].fenws)
		z.init();
}

void dfsCalcDist(int l, int x, int p = -1, lint d = 0) {
	ds[l][x].dist = d;
	for (auto &y : gph[x]) {
		if (y.pos != p && !vis[y.pos]) {
			dfsCalcDist(l, y.pos, x, d + y.rlen);
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

void update(int x, lint v) {
	int ppe = -1;
	for (int i = x; i != -1; i = par[i]) {
		lint d = v - ds[dep[i]][x].dist;
		//	cout << "add " << i << " " << d << endl;
		assoc[i].upd(i, d);
		if (ppe != -1)
			assoc[i].upd(ppe, d);
		ppe = pae[i];
	}
}

lint query(int e) {
	lint ret = 0;
	for (auto &z : idxToFenwick[e]) {
		//	cout << z[0] << " " << z[1] << " " << z[2] << endl;
		ret += (z[1] == z[0] ? +1 : -1) * assoc[z[0]].query(z[1], z[2]);
		//	cout << ret << endl;
	}
	return ret;
}

} // namespace CD

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		CD::addEdge(u, {i + n, w, 0});
		CD::addEdge(v, {i + n, w, 0});
		CD::addEdge(i + n, {u, 0, w});
		CD::addEdge(i + n, {v, 0, w});
	}
	CD::init();
	int q;
	cin >> q;
	while (q--) {
		string t;
		int v;
		cin >> t >> v;
		v--;
		if (t == "+") {
			int r;
			cin >> r;
			CD::update(v, r);
		} else {
			cout << CD::query(v + n) << "\n";
		}
	}
}