#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q, m;
	cin >> n >> q >> m;
	int s, e;
	cin >> s >> e;
	vector<lint> dist(n, 1e18);
	dist[s] = 0;
	for (int i = 0; i < q; i++) {
		vector<lint> nxt = dist;
		for (int j = 0; j < m; j++) {
			int u, v, w;
			cin >> u >> v >> w;
			nxt[u] = min(nxt[u], dist[v] + w);
			nxt[v] = min(nxt[v], dist[u] + w);
		}
		dist = nxt;
	}
	if (dist[e] > 1e17)
		dist[e] = -1;
	cout << dist[e] << "\n";
}