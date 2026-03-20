#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

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
} dsu;

vector<vector<pi>> gph;
vector<int> par, pae, dep, pa;
void dfs(int x, int p = -1) {
	pa[x] = x;
	for (auto &[id, y] : gph[x]) {
		if (p == id)
			continue;
		par[y] = x;
		pae[y] = id;
		dep[y] = dep[x] + 1;
		dfs(y, id);
	}
}

int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }

vector<int> get_path(int u, int v) {
	vector<int> ans;
	while (1) {
		u = find(u);
		v = find(v);
		if (dep[u] > dep[v])
			swap(u, v);
		if (u == v)
			break;
		pa[v] = par[v];
		ans.push_back(pae[v]);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<pi> edges(m);
	dsu.init(n);
	for (auto &[x, y] : edges) {
		cin >> x >> y;
		x--;
		y--;
	}
	cr(gph, n);
	cr(par, n);
	cr(pae, n);
	cr(pa, n);
	cr(dep, n);
	vector<int> ans(m, -2);
	vector<int> is_tree(m);
	for (int i = 0; i < sz(edges); i++) {
		if (dsu.uni(edges[i][0], edges[i][1])) {
			gph[edges[i][0]].push_back({i, edges[i][1]});
			gph[edges[i][1]].push_back({i, edges[i][0]});
			is_tree[i] = 1;
		}
	}
	dfs(0, -1);
	for (int i = 0; i < sz(edges); i++) {
		if (is_tree[i])
			continue;
		vector<int> elist = get_path(edges[i][0], edges[i][1]);
		ans[i] = i;
		for (auto &y : elist)
			ans[y] = i;
	}
	for (auto &x : ans)
		cout << x + 1 << " ";
}