#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<array<int, 3>>> gph;
vector<int> par, vis;
vector<int> ans;
vector<array<int, 3>> edges;
vector<map<int, int>> instk;
vector<set<int>> whoit;

void dfs(int e) {
	vis[e] = 1;
	if (sz(ans) == 0 && sz(instk[edges[e][1]])) {
		for (auto &[k, idx] : instk[edges[e][1]]) {
			if (k == edges[e][2])
				continue;
			for (int j = e; j != idx; j = par[j])
				ans.push_back(j + 1);
			ans.push_back(idx + 1);
			return;
		}
	}
	bool done = false;
	if (instk[edges[e][0]].count(edges[e][2]) == 0) {
		done = true;
		instk[edges[e][0]][edges[e][2]] = e;
	}
	if (whoit[edges[e][1]].count(edges[e][2]) == 0 && sz(whoit[edges[e][1]]) < 3) {
		whoit[edges[e][1]].insert(edges[e][2]);
		for (auto &[v, w, idx] : gph[edges[e][1]]) {
			if (edges[e][2] == edges[idx][2])
				continue;
			if (!vis[idx]) {
				par[idx] = e;
				dfs(idx);
			}
		}
	}
	if (done) {
		instk[edges[e][0]].erase(edges[e][2]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		cr(gph, n);
		cr(par, m);
		cr(instk, n);
		cr(whoit, n);
		ans.clear();
		edges.clear();
		for (int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			u--;
			v--;
			gph[u].push_back({w, v, i});
			edges.push_back({u, v, w});
		}
		for (int i = 0; i < n; i++)
			sort(all(gph[i]));
		cr(vis, m);
		for (int i = 0; i < m; i++) {
			if (vis[i])
				continue;
			dfs(i);
			if (sz(ans))
				break;
		}
		if (!sz(ans))
			cout << "NO\n";
		else {
			reverse(all(ans));
			cout << "YES\n" << sz(ans);
			for (auto &idx : ans)
				cout << " " << idx;
			cout << "\n";
		}
	}
}