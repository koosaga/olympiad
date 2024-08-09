vector<pi> gph[MAXN];

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
