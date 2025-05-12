#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> gph;

void dfs(int x) {
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		dfs(y);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	cr(gph, n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	vector<pi> edges;
	int vtx = n;
	for (int i = 0; i < n; i++) {
		if (sz(gph[i]) == 0)
			continue;
		auto v = gph[i];
		for (int j = 0; j < 10; j++) {
			vector<int> w;
			for (int k = 0; k < sz(v); k += 2) {
				if (k + 1 < sz(v)) {
					edges.push_back({vtx, v[k]});
					edges.push_back({vtx, v[k + 1]});
					w.push_back(vtx++);
				} else {
					edges.push_back({vtx, v[k]});
					w.push_back(vtx++);
				}
			}
			v = w;
		}
		assert(sz(v) <= 2);
		for (auto &k : v) {
			edges.push_back({k, i});
		}
	}
	cout << vtx << "\n";
	for (auto &[u, v] : edges)
		cout << 1 + u << " " << 1 + v << "\n";
}