#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<pi>> gph;
vector<int> ord, seq;
vector<int> vis, w;

void dfs(int x) {
	vis[x] = 1;
	seq.push_back(x);
	int cnt = sz(gph) + 69;
	for (auto &[i, y] : gph[x]) {
		if (!vis[y]) {
			w[i] = --cnt;
			dfs(y);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	cr(gph, n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back({i, v});
		gph[v].push_back({i, u});
	}
	cr(ord, n);
	cr(vis, n);
	cr(w, m);
	fill(all(ord), -1);
	fill(all(w), 1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		ord[x] = i;
	}
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]), [&](pi x, pi y) { return ord[x[1]] < ord[y[1]]; });
	}
	dfs(0);
	for (int i = 0; i < n; i++) {
		if (ord[seq[i]] != i) {
			cout << "impossible\n";
			return 0;
		}
	}
	for (auto &x : w)
		cout << x << " ";
}