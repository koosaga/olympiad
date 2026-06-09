#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
vector<pi> gph[800004];

vector<lint> dijkstra(int s, int n) {
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	vector<lint> dist(n, 1e18);
	auto enq = [&](int x, lint v) {
		if (dist[x] > v) {
			dist[x] = v;
			pq.push({v, x});
		}
	};
	enq(s, 0);
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (dist[x[1]] != x[0])
			continue;
		for (auto &[w, y] : gph[x[1]])
			enq(y, w + x[0]);
	}
	return dist;
}

void add_edge(int s, int e, lint x) { gph[s].push_back({x, e}); }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> events(n);
	vector<array<int, 3>> edges;
	for (int i = 0; i < m; i++) {
		int s, e, x;
		cin >> s >> e >> x;
		s--;
		e--;
		for (int j = 0; j < 2; j++) {
			swap(s, e);
			events[s].push_back(x);
			events[e].push_back(x);
			edges.push_back({s, e, x});
		}
	}
	vector<int> idx(n + 1);
	for (int i = 0; i < n; i++) {
		sort(all(events[i]));
		events[i].resize(unique(all(events[i])) - events[i].begin());
		idx[i + 1] = idx[i] + sz(events[i]);
	}
	for (auto &[s, e, x] : edges) {
		int l = lower_bound(all(events[s]), x) - events[s].begin();
		l += idx[s];
		int r = lower_bound(all(events[e]), x) - events[e].begin();
		r += idx[e];
		add_edge(l, r, x);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < sz(events[i]) - 1; j++) {
			add_edge(idx[i] + j, idx[i] + j + 1, events[i][j + 1] - events[i][j]);
			add_edge(idx[i] + j + 1, idx[i] + j, 0);
		}
	}
	for (int i = 0; i < sz(events[0]); i++) {
		add_edge(4 * m, i, events[0][i]);
	}
	for (int i = 0; i < sz(events[n - 1]); i++) {
		add_edge(idx[n - 1] + i, 4 * m + 1, 0);
	}
	cout << dijkstra(4 * m, 4 * m + 2)[4 * m + 1] << "\n";
}