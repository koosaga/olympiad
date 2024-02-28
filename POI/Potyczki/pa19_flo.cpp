#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;
const int MAXN = 2005;

lint apsp[MAXN][MAXN], d[2][MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pi>> gph(n), rev(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		rev[v].push_back({w, u});
	}
	memset(apsp, 0x3f, sizeof(apsp));
	for (int i = 0; i < n; i++) {
		apsp[i][i] = 0;
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		pq.push({0, i});
		while (sz(pq)) {
			auto x = pq.top();
			pq.pop();
			if (apsp[i][x[1]] != x[0])
				continue;
			for (auto &[w, y] : gph[x[1]]) {
				if (apsp[i][y] > apsp[i][x[1]] + w) {
					apsp[i][y] = apsp[i][x[1]] + w;
					pq.push({apsp[i][y], y});
				}
			}
		}
	}
	for (int t = 0; t < 2; t++) {
		for (int i = 0; i < n; i++) {
			vector<lint> dist(n, 1e18);
			dist[i] = 0;
			priority_queue<pi, vector<pi>, greater<pi>> pq;
			pq.push({0, i});
			while (sz(pq)) {
				auto x = pq.top();
				pq.pop();
				if (dist[x[1]] != x[0])
					continue;
				for (auto &[w, y] : gph[x[1]]) {
					if ((x[1] > i) && (y > i))
						continue;
					if (dist[y] > dist[x[1]] + w) {
						dist[y] = dist[x[1]] + w;
						pq.push({dist[y], y});
					}
				}
			}
			auto dp = dist;
			for (int i = 0; i < n; i++) {
				for (auto &[w, j] : gph[i]) {
					if (j < i)
						dp[j] = min(dp[j], dist[i] + w);
				}
			}
			for (int i = 0; i < n; i++) {
				for (auto &[w, j] : gph[i]) {
					if (j > i)
						dp[j] = min(dp[j], dp[i] + w);
				}
			}
			for (int j = 0; j < n; j++)
				if (j >= i)
					d[t][i][j] = dp[j];
		}
		swap(gph, rev);
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			lint od = apsp[i][j];
			lint nd = (i < j ? d[0][i][j] : d[1][j][i]);
			if (od > 1e14)
				od = -1;
			if (nd > 1e14)
				nd = -1;
			//	cout << od << " " << nd << endl;
			if (nd != od)
				ans++;
		}
	}
	cout << ans << "\n";
}