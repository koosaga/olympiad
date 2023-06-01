namespace AllDirectionTreeDP {

// Need to implement four functions:
// E: identity
// take_vertex: add vertex on top of merged edges
// up_root: update child DP to consider parent edge values
// merge: merge two child edges
// merge need to be commutative, whatever that means

elem E() { return elem{mint(0), mint(0)}; }
elem take_vertex(elem DP, int v) { return elem{DP[0] + a[v], DP[1] + mint(1)}; }
elem up_root(elem DP, int e) { return elem{DP[0] * b[e] + DP[1] * c[e], DP[1]}; }
elem merge(elem a, elem b) { return elem{a[0] + b[0], a[1] + b[1]}; }

void dfs(int x, vector<vector<pi>> &gph, vector<int> &ord, vector<int> &pae) {
	ord.push_back(x);
	for (auto &[i, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pi{i ^ 1, x}));
		pae[y] = (i ^ 1);
		dfs(y, gph, ord, pae);
	}
}

vector<elem> solve(int n, vector<pi> edges) {
	vector<vector<pi>> gph(n);
	gph.resize(n);
	for (int i = 0; i < n - 1; i++) {
		gph[edges[i][0]].push_back({2 * i, edges[i][1]});
		gph[edges[i][1]].push_back({2 * i + 1, edges[i][0]});
	}
	vector<int> ord;
	vector<int> pae(n, -1);
	dfs(0, gph, ord, pae);
	vector<elem> dp(n, E());
	reverse(all(ord));
	for (auto &z : ord) {
		for (auto &[i, y] : gph[z]) {
			dp[z] = merge(dp[z], up_root(dp[y], i));
		}
		dp[z] = take_vertex(dp[z], z);
	}
	vector<elem> rev_dp(n, E());
	reverse(all(ord));
	for (auto &z : ord) {
		vector<elem> pref(sz(gph[z]) + 1);
		vector<elem> suff(sz(gph[z]) + 1, E());
		if (~pae[z])
			pref[0] = up_root(rev_dp[z], pae[z]);
		for (int i = 0; i < sz(gph[z]); i++) {
			pref[i + 1] = suff[i] = up_root(dp[gph[z][i][1]], gph[z][i][0]);
		}
		for (int i = 1; i <= sz(gph[z]); i++)
			pref[i] = merge(pref[i - 1], pref[i]);
		for (int i = sz(gph[z]) - 1; i >= 0; i--)
			suff[i] = merge(suff[i], suff[i + 1]);
		for (int i = 0; i < sz(gph[z]); i++) {
			rev_dp[gph[z][i][1]] = take_vertex(merge(pref[i], suff[i + 1]), z);
		}
	}
	vector<elem> sln(n, E());
	for (int x = 0; x < n; x++) {
		if (~pae[x])
			sln[x] = up_root(rev_dp[x], pae[x]);
		for (auto &[i, y] : gph[x]) {
			sln[x] = merge(sln[x], up_root(dp[y], i));
		}
		sln[x] = take_vertex(sln[x], x);
	}
	return sln;
}

} // namespace AllDirectionTreeDP
