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

vector<vector<int>> solve_directed(int n, vector<pi> edges) {
	if (sz(edges) == 0)
		return {};
	vector<int> indeg(n);
	cr(gph, n);
	cr(ptr, n);
	cr(ans, 0);
	for (int i = 0; i < sz(edges); i++) {
		auto [u, v] = edges[i];
		gph[u].push_back({i, v});
		indeg[v]++;
	}
	vector<vector<int>> dap;
	for (int i = 0; i < n; i++) {
		if (ptr[i] < sz(gph[i])) {
			dfs(i);
			reverse(all(ans));
			dap.push_back(ans);
			ans.clear();
		}
	}
	return dap;
}
} // namespace euler_path

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n * m);
	for (auto &x : a)
		cin >> x, x--;
	vector<pi> edges;
	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		vector<vector<int>> counts(m);
		for (int j = 0; j < m; j++) {
			counts[a[i * m + j]].push_back(i * m + j);
		}
		for (int j = 0; j < m; j++) {
			if (sz(counts[j]) < 1)
				edges.push_back({j + n, i});
			for (int k = 0; k < sz(counts[j]) - 1; k++) {
				edges.push_back({i, j + n});
				mp[sz(edges) - 1] = counts[j][k];
			}
		}
	}
	vector<pi> ans;
	auto d = euler_path::solve_directed(n + m, edges);
	for (auto &v : d) {
		reverse(all(v));
		int prv = n * m;
		for (auto &j : v) {
			if (mp.count(j)) {
				ans.push_back({mp[j], prv});
				prv = mp[j];
			}
		}
		ans.push_back({n * m, prv});
	}
	cout << sz(ans) << "\n";
	for (auto &[a, b] : ans)
		cout << a + 1 << " " << b + 1 << "\n";
}