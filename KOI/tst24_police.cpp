#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;

struct frac {
	lint a, b;
	bool operator<(const frac &x) const { return a * x.b < b * x.a; }
	bool operator<=(const frac &x) const { return a * x.b <= b * x.a; }
	bool operator>(const frac &x) const { return x < *this; }
	bool operator>=(const frac &x) const { return x <= *this; }
	bool operator==(const frac &x) const { return a * x.b == b * x.a; }
	frac operator+(const frac &f) const { return {a + f.a, b + f.b}; }
	frac operator-(const frac &f) const { return {a - f.a, b - f.b}; }
};
const int MAXN = 100005;

vector<int> weights;
lint pfar[MAXN], far[MAXN];

namespace AllDirectionTreeDP {

// Need to implement four functions:
// E: identity
// take_vertex: add vertex on top of merged edges
// up_root: update child DP to consider parent edge values
// merge: merge two child edges
// it's good if merges are commutative (its not necessary but be careful of specifics)

using elem = lint;
elem E() { return 0; }
elem take_vertex(elem DP, int v) { return DP; }
elem up_root(elem DP, int e) { return DP + weights[e / 2]; }
elem merge(elem a, elem b) { return max(a, b); }

void dfs(int x, vector<vector<pi>> &gph, vector<int> &ord, vector<int> &pae) {
	ord.push_back(x);
	for (auto &[i, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pi{i ^ 1, x}));
		pae[y] = (i ^ 1);
		dfs(y, gph, ord, pae);
	}
}

void solve(int n, vector<pi> edges) {
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
	for (int i = 0; i < n; i++)
		far[i] = dp[i];
	for (int i = 1; i < n; i++)
		pfar[i] = rev_dp[i];
}

} // namespace AllDirectionTreeDP

vector<pi> gph[MAXN];
lint dist[MAXN];
int par[17][MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;

void dfs(int x, int p) {
	din[x] = piv++;
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			dist[y] = dist[x] + w;
			par[0][y] = x;
			dfs(y, x);
		}
	}
	dout[x] = piv;
}

int anc(int x, int d) {
	for (int i = 0; d; i++) {
		if (d & 1)
			x = par[i][x];
		d >>= 1;
	}
	return x;
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1) {
			v = par[i][v];
		}
		dx >>= 1;
	}
	if (u == v)
		return u;
	for (int i = 16; i >= 0; i--) {
		if (par[i][u] != par[i][v]) {
			u = par[i][u];
			v = par[i][v];
		}
	}
	return par[0][u];
}

lint farf(int x, int p) {
	if (par[0][x] == p)
		return far[x];
	return pfar[p];
}

lint distf(int x, int y) { return dist[x] + dist[y] - 2 * dist[lca(x, y)]; }

vector<array<long long, 2>> police_thief(vector<int> A, vector<int> B, vector<int> D, vector<int> P, vector<int> V1, vector<int> T, vector<int> V2) {
	int n = sz(A) + 1;
	vector<pi> edges;
	for (int i = 0; i < n - 1; i++) {
		gph[A[i]].push_back({D[i], B[i]});
		gph[B[i]].push_back({D[i], A[i]});
		weights.push_back(D[i]);
		edges.push_back({A[i], B[i]});
	}
	AllDirectionTreeDP::solve(n, edges);
	dfs(0, -1);
	for (int i = 1; i < 17; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	int q = sz(P);
	vector<pi> ans;
	for (int i = 0; i < q; i++) {
		int p = P[i], t = T[i], v1 = V1[i], v2 = V2[i];
		int l = lca(p, t);
		lint d = (dist[p] - dist[l]) + (dist[t] - dist[l]);
		int W = -1, pW = -1;
		// in path (l..t]
		if (frac{dist[p] - dist[l], d} <= frac{v1, v1 + v2}) {
			W = t;
			for (int i = 16; i >= 0; i--) {
				if (dep[W] - dep[l] > (1 << i) && frac{dist[p] - dist[l] + dist[par[i][W]] - dist[l], d} > frac{v1, v1 + v2}) {
					W = par[i][W];
				}
			}
			pW = par[0][W];
		} else {
			W = p;
			for (int i = 16; i >= 0; i--) {
				if (dep[W] - dep[l] >= (1 << i) && frac{dist[p] - dist[par[i][W]], d} <= frac{v1, v1 + v2}) {
					W = par[i][W];
				}
			}
			pW = W;
			W = par[0][W];
		}
		if (v1 <= v2) {
			auto z = frac{distf(p, W) + farf(W, pW), v1};
			ans.push_back({z.a, z.b});
		} else {
			auto in = [&](int s, int t) { return din[s] <= din[t] && dout[t] <= dout[s]; };
			auto predicate = [&](int q) {
				int qw = -1;
				if (in(q, p))
					qw = anc(p, dep[p] - dep[q] - 1);
				else
					qw = par[0][q];
				lint dd = distf(p, q);
				frac k1 = {farf(q, qw) + dd, v1};
				frac k2 = {2 * dd - d, v1 - v2};
				if (k1 <= k2)
					return make_pair(true, k1);
				else
					return make_pair(false, k2);
			}; // false -> true
			auto p1 = predicate(t);
			if (p1.first == 0) {
				ans.push_back({p1.second.a, p1.second.b});
				continue;
			}
			auto p2 = predicate(W);
			if (p2.first == 1) {
				ans.push_back({p2.second.a, p2.second.b});
				continue;
			}
			int l = lca(W, t);
			auto pl = predicate(l);
			if (pl.first) {
				int v = W;
				for (int i = 16; i >= 0; i--) {
					if (dep[v] - dep[l] > (1 << i) && predicate(par[i][v]).first == 0) {
						v = par[i][v];
					}
				}
				auto dap = max(predicate(v).second, predicate(par[0][v]).second);
				ans.push_back({dap.a, dap.b});
			} else {
				int v = t;
				for (int i = 16; i >= 0; i--) {
					if (dep[v] - dep[l] > (1 << i) && predicate(par[i][v]).first) {
						v = par[i][v];
					}
				}
				auto dap = max(predicate(v).second, predicate(par[0][v]).second);
				ans.push_back({dap.a, dap.b});
			}
		}
	}

	return ans;
}