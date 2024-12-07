
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

#include "tree.h"
using namespace std;

struct node {
	lint inside_mx;
	lint root_cont_mx; // must contain something
};

vector<lint> a;

namespace AllDirectionTreeDP {

// Need to implement four functions:
// E: identity
// take_vertex: add vertex on top of merged edges
// up_root: update child DP to consider parent edge values
// merge: merge two child edges
// it's good if merges are commutative (its not necessary but be careful of specifics)
using elem = node;

elem E() { return node{lint(-1e18), lint(-1e18)}; }
elem take_vertex(elem DP, int v) { return node{max(DP.inside_mx, max(0ll, DP.root_cont_mx) + a[v]), max(DP.root_cont_mx, 0ll) + a[v]}; }
elem up_root(elem DP, int e) { return DP; }
elem merge(elem a, elem b) { return node{max(a.inside_mx, b.inside_mx), max({a.root_cont_mx + b.root_cont_mx, a.root_cont_mx, b.root_cont_mx})}; }

void dfs(int x, vector<vector<pi>> &gph, vector<int> &ord, vector<int> &pae) {
	ord.push_back(x);
	for (auto &[i, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pi{i ^ 1, x}));
		pae[y] = (i ^ 1);
		dfs(y, gph, ord, pae);
	}
}

lint solve(int n, vector<pi> edges) {
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
		vector<elem> pref(sz(gph[z]) + 1, E());
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
	lint ans = -1e18;
	for (int x = 0; x < n; x++) {
		vector<lint> toptwo;
		if (x > 0)
			toptwo.push_back(rev_dp[x].inside_mx);
		for (auto &[_, j] : gph[x]) {
			toptwo.push_back(dp[j].inside_mx);
		}
		if (sz(toptwo) >= 2) {
			sort(all(toptwo));
			ans = max(ans, toptwo[sz(toptwo) - 2] + toptwo.back());
		}
	}
	return ans;
}

} // namespace AllDirectionTreeDP
long long findSum(int N, std::vector<int> C, std::vector<int> Node1, std::vector<int> Node2) {
	for (int i = 0; i < N; i++)
		a.push_back(C[i]);
	vector<pi> edges;
	for (int i = 0; i < N - 1; i++) {
		edges.push_back({Node1[i], Node2[i]});
	}
	return AllDirectionTreeDP::solve(N, edges);
}
