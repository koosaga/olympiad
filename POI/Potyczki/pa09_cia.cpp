#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	vector<vector<pi>> gph(n);
	vector<int> deg(n), tri(m);
	vector<pi> edges;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		assert(u != v);
		edges.push_back({u, v});
		deg[u]++;
		deg[v]++;
	}
	lint ans = 0;
	sort(all(edges));
	cr(gph, n);
	for (int i = 0; i < m; i++) {
		auto [u, v] = edges[i];
		if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v))
			swap(u, v);
		gph[u].push_back({i, v});
	}
	vector<int> val(n, -1);
	for (int aa = 0; aa < n; aa++) {
		for (auto [i, b] : gph[aa])
			val[b] = i;
		for (auto [i, b] : gph[aa]) {
			for (auto [j, c] : gph[b]) {
				if (~val[c]) {
					ans += max({a[aa], a[b], a[c]});
				}
			}
		}
		for (auto [i, b] : gph[aa])
			val[b] = -1;
	}
	cout << ans << "\n";
}