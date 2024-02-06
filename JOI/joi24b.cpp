#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, m, s, t, l, k;
	cin >> n >> m >> s >> t >> l >> k;
	s--;
	t--;
	vector<vector<pi>> gph(n);
	for (int i = 0; i < m; i++) {
		lint s, e, x;
		cin >> s >> e >> x;
		gph[s - 1].push_back({x, e - 1});
		gph[e - 1].push_back({x, s - 1});
	}
	vector<lint> d1(n, 1e18), d2(n, 1e18);
	auto dijkstra = [&](int s, vector<lint> &dist) {
		priority_queue<pi, vector<pi>, greater<pi>> pq;
		dist[s] = 0;
		pq.push({0, s});
		while (sz(pq)) {
			auto x = pq.top();
			pq.pop();
			if (dist[x[1]] != x[0])
				continue;
			for (auto &[w, y] : gph[x[1]]) {
				if (dist[y] > x[0] + w) {
					dist[y] = x[0] + w;
					pq.push({dist[y], y});
				}
			}
		}
	};
	dijkstra(s, d1);
	dijkstra(t, d2);
	if (d1[t] <= k) {
		cout << 1ll * n * (n - 1) / 2 << "\n";
		return 0;
	}
	sort(all(d1));
	sort(all(d2));
	int j = n;
	lint ans = 0;
	for (int i = 0; i < n; i++) {
		while (j && d1[i] + l + d2[j - 1] > k)
			j--;
		ans += j;
	}
	cout << ans << "\n";
}