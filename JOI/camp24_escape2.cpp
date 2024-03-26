#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int SEX = 500;

lint par[MAXN], pae[MAXN], len[MAXN], lvl[MAXN], cost[MAXN];
vector<pi> queries[MAXN];
lint ans[MAXN * 3];
lint prec[205][MAXN];

vector<pi> gph[MAXN];

void dfs(int x) {
	for (auto &[r, idx] : queries[lvl[x]]) {
		ans[idx] = min(ans[idx], len[x] + cost[lvl[x]] - cost[r - 1]);
	}
	for (auto &[w, y] : gph[x]) {
		cost[lvl[y]] = cost[lvl[x]] + w;
		dfs(y);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, t;
	cin >> n >> t;
	vector<vector<pi>> adj(n - 1);
	for (auto &v : adj) {
		int q;
		cin >> q;
		vector<pi> w(q);
		for (auto &[x, y] : w) {
			cin >> x >> y;
		}
		sort(all(w), [&](const pi &a, const pi &b) {
			if (a[1] != b[1])
				return a[1] < b[1];
			return a[0] > b[0];
		});
		for (auto &[x, y] : w) {
			if (sz(v) == 0 || v.back()[0] < x) {
				v.push_back({x, y});
			}
		}
	}
	vector<vector<int>> indices(n - 1);
	vector<int> intervals(n + 1);
	int V = 1;
	for (int i = n - 2; i >= 0; i--) {
		indices[i].resize(sz(adj[i]));
		iota(all(indices[i]), V);
		V += sz(indices[i]);
	}
	for (int i = n - 2; i >= 0; i--) {
		if (i == n - 2) {
			for (int j = 0; j < sz(indices[i]); j++) {
				par[indices[i][j]] = 0;
				pae[indices[i][j]] = 0;
				len[indices[i][j]] = adj[i][j][1] - adj[i][j][0];
				lvl[indices[i][j]] = i;
			}
		} else {
			for (int j = 0; j < sz(indices[i]); j++) {
				len[indices[i][j]] = adj[i][j][1] - adj[i][j][0];
				lvl[indices[i][j]] = i;
				int l = lower_bound(all(adj[i + 1]), pi{adj[i][j][1], -1}) - adj[i + 1].begin();
				l %= sz(adj[i + 1]);
				par[indices[i][j]] = indices[i + 1][l];
				pae[indices[i][j]] = len[indices[i + 1][l]] + (adj[i + 1][l][0] - adj[i][j][1] + t) % t;
			}
		}
	}
	int q;
	cin >> q;
	vector<int> label(n);
	vector<vector<lint>> prec;
	vector<lint> dp(V);
	for (int i = 0; i < n - 1; i++) {
		if (sz(adj[i]) > SEX) {
			label[i] = sz(prec);
			fill(all(dp), 1e18);
			vector<lint> ans(n, 1e18);
			for (auto &v : indices[i]) {
				dp[v] = len[v];
			}
			for (int j = indices[i].back(); j > 0; j--) {
				dp[par[j]] = min(dp[par[j]], dp[j] + pae[j]);
			}
			for (int j = 1; j <= indices[i].back(); j++) {
				ans[lvl[j] + 1] = min(ans[lvl[j] + 1], dp[j]);
			}
			prec.push_back(ans);
		}
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		if (sz(adj[l]) <= SEX) {
			queries[l].push_back({r, i});
		} else {
			ans[i] = prec[label[l]][r];
		}
	}
	for (int i = 1; i < V; i++) {
		// cout << par[i] << " " << i << " " << pae[i] << endl;
		gph[par[i]].push_back({pae[i], i});
	}
	lvl[0] = n - 1;
	for (int i = 0; i < n; i++) {
		sort(all(queries[i]));
		vector<pi> v;
		for (int j = 0; j < sz(queries[i]);) {
			int k = j;
			while (k < sz(queries[i]) && queries[i][j][0] == queries[i][k][0])
				k++;
			v.push_back(queries[i][j]);
			ans[queries[i][j][1]] = 1e18;
			for (int x = j + 1; x < k; x++)
				ans[queries[i][x][1]] = ~queries[i][j][1];
			j = k;
		}
		queries[i] = v;
	}
	dfs(0);
	for (int i = 0; i < q; i++) {
		if (ans[i] < 0) {
			ans[i] = ans[~ans[i]];
		}
		cout << ans[i] << "\n";
	}
}