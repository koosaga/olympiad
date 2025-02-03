// A nonempty subset X \subseteq V is an extreme set of f (cut fn. here)
// if f(Y) > f(X) holds for all proper nonempty subset of X.
// They form a laminar family, which follows from the submodularity of f.
//
// Given a simple weighted undirected graph as a list of edges
// returns a (laminar representation) tree of 2n-1 vertices, rooted at 2n-2
// where for each rooted subtree, its set of leafs form a extreme set
// specifically, the largest nontrivial subtree is a global min-cut.
//
// O(nm log n)
// Credit: Ayanaa6 (https://judge.yosupo.jp/submission/216101)

vector<vector<int>> EVS(int n, vector<array<lint, 3>> edges) {
	vector<vector<pi>> g(2 * n - 1);
	for (auto &[u, v, w] : edges) {
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	vector<vector<int>> tr = vector<vector<int>>(2 * n - 1);
	vector<lint> used(2 * n - 1, 1);
	for (int i = 0; i < n - 1; i++) {
		g.push_back(vector<pi>());
		vector<int> ord(n - i), vis(n + i);
		vector<lint> cost(n + i);
		priority_queue<pi> que;
		for (int j = 0; j < n + i; j++)
			if (used[j]) {
				for (auto p : g[j])
					cost[j] += p[1];
				que.push({-cost[j], j});
			}
		for (int j = 0; j < n - i; j++)
			while (1) {
				auto pr = que.top();
				que.pop();
				int v = pr[1];
				if (vis[v])
					continue;
				vis[v] = 1;
				ord[j] = v;
				for (auto p : g[v]) {
					int u = p[0];
					if (!vis[u]) {
						cost[u] -= p[1];
						que.push({-cost[u], u});
					}
				}
				break;
			}
		int v0 = ord[n - i - 1], v1 = ord[n - i - 2];
		g[v0].clear(), g[v1].clear();
		used[v0] = used[v1] = 0;
		for (int j = 0; j < n + i; j++)
			if (used[j])
				for (auto &p : g[j]) {
					int u = p[0];
					if (u == v0 || u == v1) {
						p[0] = n + i;
						g[n + i].push_back({j, p[1]});
					}
				}
		tr[n + i].push_back(v0);
		tr[n + i].push_back(v1);
	}
	return tr;
}
