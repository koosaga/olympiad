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
	int n, m;
	cin >> n >> m;
	vector<vector<array<int, 3>>> gph(n);
	vector<pi> edges, ecnt;
	vector<lint> f(n);
	for (int i = 0; i < n; i++)
		cin >> f[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back({i, v, 0});
		gph[v].push_back({i, u, 0});
	}
	vector<int> route(m);
	iota(all(route), 0);
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]),
			 [&](const array<int, 3> &a, const array<int, 3> &b) { return pi{a[1], a[0]} < pi{b[1], b[0]}; });
		vector<array<int, 3>> fuck;
		for (auto &[idx, j, v] : gph[i]) {
			if (sz(fuck) && fuck.back()[1] == j) {
				route[idx] = fuck.back()[0];
				fuck.back()[2]++;
				continue;
			} else {

				fuck.push_back({idx, j, 1});
			}
		}
		gph[i] = fuck;
	}
	vector<int> ord(n), mark(n);
	vector<multiset<lint>> counts(n);
	iota(all(ord), 0);
	lint ans = -1;
	sort(all(ord), [&](const int &a, const int &b) { return sz(gph[a]) > sz(gph[b]); });
	for (auto &v : ord) {
		mark[v] = 1;
		for (auto &[_, a, ma] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[_, b, mb] : gph[a]) {
				if (!mark[b])
					counts[b].insert(f[a]);
			}
		}
		for (auto &[e, a, ma] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[_, b, mb] : gph[a]) {
				if (!mark[b]) {
					counts[b].erase(counts[b].find(f[a]));
					if (sz(counts[b]))
						ans = max(ans, f[v] + f[a] + *counts[b].rbegin() + f[b]);
					counts[b].insert(f[a]);
				}
			}
		}
		for (auto &[e, a, _] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[f, b, __] : gph[a]) {
				counts[b].clear();
			}
		}
	}
	cout << ans << "\n";
}