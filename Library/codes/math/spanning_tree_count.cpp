mint undirectedSpanningTreeCount(int n, vector<vector<mint>> adj) {
	if (n == 1)
		return 1;
	n--;
	vector<vector<mint>> laplacian(n, vector<mint>(n));
	for (int u = 0; u <= n; u++) {
		for (int v = 0; v <= n; v++) {
			if (u < n && v < n)
				laplacian[u][v] -= adj[u][v];
			if (u < n)
				laplacian[u][u] += adj[u][v];
		}
	}
	auto [aa, rank, det, c] = Gauss(laplacian);
	return det;
}

mint directedSpanningTreeCount(int n, int r, vector<vector<mint>> adj) {
	if (n == 1)
		return 1;
	n--;
	vector<vector<mint>> a(n, vector<mint>(n));
	for (int u = 0; u <= n; u++) {
		for (int v = 0; v <= n; v++) {
			if (u != r && v != r)
				a[v - (v > r)][u - (u > r)] -= adj[u][v];
			if (v != r)
				a[v - (v > r)][v - (v > r)] += adj[u][v];
		}
	}
	auto [aa, rank, det, c] = Gauss(a);
	return det;
}

mint eulerianCircuitCount(int n, vector<vector<int>> adj) {
	mint ans = 1;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int ind = 0, outd = 0;
		for (int j = 0; j < n; j++) {
			ind += adj[i][j];
			outd += adj[j][i];
		}
		if (ind != outd)
			return 0;
		if (ind)
			v.push_back(i);
		for (int j = 1; j < ind; j++)
			ans *= mint(j);
	}
	if (sz(v) == 0)
		return 1;
	vector<vector<mint>> adj2(sz(v), vector<mint>(sz(v)));
	for (int i = 0; i < sz(v); i++) {
		for (int j = 0; j < sz(v); j++) {
			adj2[i][j] = adj[v[i]][v[j]];
		}
	}
	return directedSpanningTreeCount(sz(v), 0, adj2) * ans;
}