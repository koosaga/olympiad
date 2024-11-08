// Compute an adjugate matrix adj(A) where adj(A)_{ij} = (-1)^{i+j) M_{ij}
// where M_{ij} is the determinant of the matrix that is obtained from A by removing its i-th row and j-th column.
// O(n^3)
// Credit: adamant (https://judge.yosupo.jp/submission/245438)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

vector<vector<mint>> adjugate(vector<vector<mint>> a) {
	int n = sz(a);
	a.push_back(vector<mint>());
	for (int i = 0; i < n; i++) {
		a[i].push_back(randint(1, mod - 1));
		a[n].push_back(randint(1, mod - 1));
	}
	a[n].push_back(0);
	auto [ref, rank, det, inv] = Gauss(a, true);
	vector<vector<mint>> adj(n, vector<mint>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adj[i][j] = det * (inv[n][n] * inv[i][j] - inv[i][n] * inv[n][j]);
		}
	}
	return adj;
}