// For each edge, count the number of simple 4-cycle containing that edge
// m sqrt(m)
// To count for all triangles: https://www.acmicpc.net/problem/2390

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<array<int, 3>>> gph(n);
	vector<pi> edges, ecnt;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		gph[u].push_back({i, v, 0});
		gph[v].push_back({i, u, 0});
	}
	vector<int> route(m);
	iota(all(route), 0);
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]), [&](const array<int, 3> &a, const array<int, 3> &b) { return pi{a[1], a[0]} < pi{b[1], b[0]}; });
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
	vector<lint> counts(n);
	vector<lint> quads(m);
	iota(all(ord), 0);
	sort(all(ord), [&](const int &a, const int &b) { return sz(gph[a]) > sz(gph[b]); });
	for (auto &v : ord) {
		mark[v] = 1;
		for (auto &[_, a, ma] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[_, b, mb] : gph[a]) {
				if (!mark[b])
					counts[b] += 1ll * ma * mb;
			}
		}
		for (auto &[e, a, ma] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[f, b, mb] : gph[a]) {
				if (!mark[b]) {
					quads[e] += mb * (counts[b] - 1ll * ma * mb);
					quads[f] += ma * (counts[b] - 1ll * ma * mb);
				}
			}
		}
		for (auto &[e, a, _] : gph[v]) {
			if (mark[a])
				continue;
			for (auto &[f, b, __] : gph[a]) {
				if (counts[b]) {
					counts[b] = 0;
				}
			}
		}
	}
	for (int i = 0; i < m; i++)
		cout << quads[route[i]] << " ";
}