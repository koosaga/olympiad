#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct disj {
	vector<int> pa, sub;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		sub.resize(n);
		fill(all(sub), 1);
		iota(all(pa), 0);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		sub[p] += sub[q];
		return 1;
	}
	int getsz(int x) { return sub[find(x)]; }
} dsu;

vector<vector<pi>> gph;
vector<int> dfn, low;
int piv;

void dfs(int x, int p) {
	dfn[x] = low[x] = ++piv;
	for (auto &[w, y] : gph[x]) {
		if (w == p)
			continue;
		if (!dfn[y]) {
			dfs(y, w);
			if (low[y] <= dfn[x])
				dsu.uni(x, y);
			low[x] = min(low[x], low[y]);
		} else
			low[x] = min(low[x], dfn[y]);
	}
}

vector<lint> sub, dp;

lint solve(int x, int p) {
	sub[x] = dsu.getsz(x);
	vector<pi> pairs;
	lint ans = 1ll * sz(dp) * sz(dp);
	for (auto &[_, y] : gph[x]) {
		if (y == p)
			continue;
		ans = min(ans, solve(y, x));
		sub[x] += sub[y];
		pairs.push_back({sub[y], dp[y]});
	}
	dp[x] = sub[x] * sub[x];
	for (auto &[k, v] : pairs) {
		dp[x] = min(dp[x], v + 1ll * (sub[x] - k) * (sub[x] - k));
	}
	sort(all(pairs));
	{
		vector<pi> w;
		for (int i = 0; i < sz(pairs); i++) {
			if (i >= 2 && pairs[i - 2][0] == pairs[i][0])
				continue;
			w.push_back(pairs[i]);
		}
		for (int i = 0; i < sz(w); i++) {
			ans = min(ans, w[i][1] + (sz(dp) - w[i][0]) * (sz(dp) - w[i][0]));
			for (int j = 0; j < i; j++) {
				ans = min(ans, w[i][1] + w[j][1] + (sz(dp) - w[i][0] - w[j][0]) * (sz(dp) - w[i][0] - w[j][0]));
			}
		}
	}
	return ans;
}

long long max_diversity(int N, int M, vector<int> U, vector<int> V) {
	cr(gph, N);
	cr(dfn, N);
	cr(low, N);
	for (int i = 0; i < M; i++) {
		gph[U[i]].push_back({i, V[i]});
		gph[V[i]].push_back({i, U[i]});
	}
	dsu.init(N);
	dfs(0, -1);
	cr(gph, N);

	for (int i = 0; i < M; i++) {
		int a = dsu.find(U[i]);
		int b = dsu.find(V[i]);
		if (a != b) {
			gph[a].push_back({b, b});
			gph[b].push_back({a, a});
		}
	}
	cr(sub, N);
	cr(dp, N);
	return (1ll * N * N - solve(dsu.find(0), -1)) / 2;
}