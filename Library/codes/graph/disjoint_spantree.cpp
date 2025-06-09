vector<vector<vector<pi>>> gph;
vector<vector<int>> pa, par, pae, dep, comp;
vector<pi> edges;
vector<int> ans;

int up(int t, int x) { return pa[t][x] = (pa[t][x] == x ? x : up(t, pa[t][x])); }

bool augment(int t, int u, int v) {
	if (comp[t][u] != comp[t][v])
		return true;
	vector<int> nxt;
	while (true) {
		u = up(t, u);
		v = up(t, v);
		if (u == v)
			break;
		if (dep[t][u] < dep[t][v]) {
			swap(u, v);
		}
		nxt.push_back(pae[t][u]);
		pa[t][u] = par[t][u];
	}
	for (auto &e : nxt) {
		for (int k = 0; k < sz(gph); k++) {
			if (k != t && augment(k, edges[e][0], edges[e][1])) {
				ans[e] = k;
				return true;
			}
		}
	}
	return false;
}

vector<int> vis;

void dfs(int t, int x, int p = -1) {
	vis[x] = 1;
	for (auto &[i, y] : gph[t][x]) {
		if (y != p) {
			dep[t][y] = dep[t][x] + 1;
			par[t][y] = x;
			pae[t][y] = i;
			comp[t][y] = comp[t][x];
			dfs(t, y, x);
		}
	}
}

vector<int> solve(int n, int k, vector<pi> e) {
	edges = e;
	int m = sz(edges);
	cr(gph, k);
	cr(pa, k);
	cr(par, k);
	cr(pae, k);
	cr(dep, k);
	cr(comp, k);
	cr(ans, m);
	fill(all(ans), -1);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			cr(gph[j], n);
			cr(pa[j], n);
			cr(par[j], n);
			cr(pae[j], n);
			cr(dep[j], n);
			cr(comp[j], n);
			iota(all(pa[j]), 0);
		}
		for (int j = 0; j < i; j++) {
			if (ans[j] >= 0) {
				gph[ans[j]][edges[j][0]].push_back({j, edges[j][1]});
				gph[ans[j]][edges[j][1]].push_back({j, edges[j][0]});
			}
		}
		for (int j = 0; j < k; j++) {
			cr(vis, n);
			for (int x = 0; x < n; x++) {
				if (!vis[x]) {
					comp[j][x] = x;
					dep[j][x] = 0;
					dfs(j, x);
				}
			}
		}
		for (int j = 0; j < k; j++) {
			if (augment(j, edges[i][0], edges[i][1])) {
				ans[i] = j;
				break;
			}
		}
	}
	return ans;
}

