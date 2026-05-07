#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<int>> gph;
vector<int> par;
vector<int> din, dout, ord, dep, vis;

bool in(int u, int v) { return din[u] <= din[v] && dout[v] <= dout[u]; }
void dfs(int x, int p = -1) {
	din[x] = sz(ord);
	ord.push_back(x);
	vis[x] = 1;
	for (auto &y : gph[x]) {
		if (y == p)
			continue;
		if (!vis[y]) {
			par[y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
		}
	}
	dout[x] = sz(ord);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	cr(gph, n);
	cr(par, n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	cr(din, n);
	cr(dout, n);
	cr(vis, n);
	cr(dep, n);
	for (int i = 0; i < n; i++) {
		if (!vis[i])
			dfs(i);
	}
	int pos = max_element(all(dep)) - dep.begin();
	if (dep[pos] >= n - 2 * k + 1) {
		cout << "1\n";
		for (int j = 0; j < n - 2 * k + 2; j++) {
			cout << pos + 1 << "\n";
			pos = par[pos];
		}
		return 0;
	}
	cout << "2\n";
	vector<int> L(ord.end() - k, ord.end());
	vector<int> R;
	for (int j = n - k - 1; j >= 0; j--) {
		if (sz(R) < k && !in(ord[j], ord[n - k])) {
			R.push_back(ord[j]);
		}
	}
	for (auto &x : L)
		cout << x + 1 << " ";
	cout << "\n";
	for (auto &x : R)
		cout << x + 1 << " ";
	cout << "\n";
}
