#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

namespace euler_path {
vector<vector<pi>> gph;
vector<int> ptr, ans, vis;
void dfs(int x) {
	while (ptr[x] < sz(gph[x])) {
		auto [idx, z] = gph[x][ptr[x]++];
		dfs(z);
		ans.push_back(idx);
	}
}
void dfs2(int x) {
	while (ptr[x] < sz(gph[x])) {
		auto [idx, z] = gph[x][ptr[x]++];
		if (vis[idx >> 1])
			continue;
		vis[idx >> 1] = 1;
		dfs2(z);
		ans.push_back(idx);
	}
}

vector<int> solve_undirected(int n, vector<pi> edges) {
	if (sz(edges) == 0)
		return {};
	cr(gph, n);
	cr(ptr, n);
	cr(ans, 0);
	cr(vis, 2 * sz(edges));
	for (int i = 0; i < sz(edges); i++) {
		auto [u, v] = edges[i];
		gph[u].push_back({2 * i, v});
		gph[v].push_back({2 * i + 1, u});
	}
	int fixed = -1;
	int oddcnt = 0;
	for (int i = 0; i < n; i++) {
		if (sz(gph[i]) % 2 == 1) {
			oddcnt++;
			fixed = i;
		}
	}
	if (oddcnt > 2)
		return {};
	for (int i = 0; i < n; i++) {
		if (ptr[i] < sz(gph[i])) {
			dfs2(i);
		}
	}
	if (sz(ans) != sz(edges))
		ans.clear();
	return ans;
}

} // namespace euler_path

vector<vector<int>> adj;

// note: my code does not have coord compression and so has like O(st) complexity
// should be trivial to fix but i'm just too lazy to write it

void solve(int l, int r, int t) {
	if (r - l == 1)
		return;
	vector<pi> edges;
	vector<int> deg(t);
	vector<int> ptr(sz(adj));
	for (int i = 0; i < sz(adj); i++) {
		for (int j = l; j < r; j += 2) {
			edges.push_back({adj[i][j], adj[i][j + 1]});
			deg[adj[i][j]]++;
			deg[adj[i][j + 1]]++;
		}
	}
	int ecnt = sz(edges);
	int uplast = -1;
	int m = (l + r) / 2;
	for (int i = 0; i < t; i++) {
		if (deg[i] % 2 == 1) {
			if (uplast == -1)
				uplast = i;
			else {
				edges.push_back({uplast, i});
				uplast = -1;
			}
		}
	}
	auto ans = euler_path::solve_undirected(t, edges);
	assert(sz(ans));
	for (auto &ed : ans) {
		if (ed >= 2 * ecnt)
			continue;
		if (ed % 2 == 0) {
			auto [u, v] = edges[ed / 2];
			int rw = ed / (r - l);
			adj[rw][l + ptr[rw]] = u;
			adj[rw][m + ptr[rw]] = v;
			ptr[rw]++;
		}
		if (ed % 2 == 1) {
			auto [v, u] = edges[ed / 2];
			int rw = ed / (r - l);
			adj[rw][l + ptr[rw]] = u;
			adj[rw][m + ptr[rw]] = v;
			ptr[rw]++;
		}
	}
	assert(count(all(ptr), m - l) == sz(ptr));
	solve(l, m, t);
	solve(m, r, t);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, s, t;
	cin >> n >> s >> t;
	cr(adj, n);
	for (auto &x : adj) {
		x.resize(s);
		for (auto &y : x) {
			cin >> y;
			y--;
		}
	}
	solve(0, s, t);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < s; j++) {
			cout << adj[i][j] + 1 << " ";
		}
		cout << "\n";
	}
}