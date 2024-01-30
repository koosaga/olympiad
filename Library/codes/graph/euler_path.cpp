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

vector<int> solve_directed(int n, vector<pi> edges) {
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
	int fixed = -1;
	for (int i = 0; i < n; i++) {
		if (indeg[i] < sz(gph[i])) {
			if (fixed == -1 && indeg[i] + 1 == sz(gph[i]))
				fixed = i;
			else
				return {};
		}
	}
	if (fixed == -1) {
		for (int i = 0; i < n; i++) {
			if (sz(gph[i])) {
				fixed = i;
				break;
			}
		}
	}
	dfs(fixed);
	reverse(all(ans));
	if (sz(ans) != sz(edges))
		ans.clear();
	return ans;
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
	if (fixed == -1) {
		for (int i = 0; i < n; i++) {
			if (sz(gph[i])) {
				fixed = i;
				break;
			}
		}
	}
	dfs2(fixed);
	reverse(all(ans));
	if (sz(ans) != sz(edges))
		ans.clear();
	return ans;
}

} // namespace euler_path
