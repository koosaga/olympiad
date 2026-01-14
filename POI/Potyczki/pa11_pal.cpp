#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

vector<vector<int>> gph;

pi dfs(int x, int p) {
	pi ans{0, x};
	for (auto &y : gph[x]) {
		if (y != p) {
			ans = max(ans, dfs(y, x));
		}
	}
	ans[0]++;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	cr(gph, n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	m++;
	int d = dfs(dfs(0, -1)[1], -1)[0];
	for (int ans = n;; ans--) {
		int cost = 0;
		if (ans >= d)
			cost = d + 2 * (ans - d);
		else
			cost = ans;
		if (cost <= m) {
			cout << ans << "\n";
			break;
		}
	}
}