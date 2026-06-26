#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int MAXN = 500005;
vector<vector<int>> gph;
int par[19][MAXN], dep[MAXN];

void dfs(int x, int p = -1) {
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			par[0][y] = x;
			dfs(y, x);
		}
	}
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1)
			v = par[i][v];
		dx >>= 1;
	}
	if (u == v)
		return u;
	for (int i = 18; i >= 0; i--) {
		if (par[i][u] != par[i][v])
			u = par[i][u], v = par[i][v];
	}
	return par[0][u];
}

vector<int> solve(vector<string> a, vector<array<int, 4>> queries) {
	int n = sz(a);
	vector<vector<int>> idx(n, vector<int>(n, -1));
	int m = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == '.')
				continue;
			int k = j;
			while (k < n && a[i][k] == '#') {
				idx[i][k] = m;
				k++;
			}
			j = k - 1;
			m++;
		}
	}
	vector<pi> edges;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			if (~idx[i][j] && ~idx[i + 1][j])
				edges.push_back({idx[i][j], idx[i + 1][j]});
		}
	}
	cr(gph, m);
	sort(all(edges));
	edges.resize(unique(all(edges)) - edges.begin());
	for (auto &[u, v] : edges) {
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	for (int i = 1; i < 19; i++) {
		for (int j = 0; j < m; j++)
			par[i][j] = par[i - 1][par[i - 1][j]];
	}
	auto dist = [&](int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; };
	vector<int> ans;
	for (auto &[x1, y1, x2, y2] : queries) {
		ans.push_back(dist(idx[x1][y1], idx[x2][y2]));
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<string> a(n);
	for (auto &x : a)
		cin >> x;
	vector<array<int, 4>> queries(q);
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < 4; j++)
			cin >> queries[i][j], queries[i][j]--;
	}
	auto X = solve(a, queries);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++)
			swap(a[i][j], a[j][i]);
	}
	for (auto &[x1, y1, x2, y2] : queries)
		swap(x1, y1), swap(x2, y2);
	auto Y = solve(a, queries);
	for (int i = 0; i < q; i++)
		cout << X[i] + Y[i] << "\n";
}