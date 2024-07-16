#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 300005;

vector<pi> gph[MAXN];
vector<int> dfn;
int vis[MAXN], sz[MAXN], msz[MAXN];

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y[1] != p && !vis[y[1]]) {
			dfs(y[1], x);
			sz[x] += sz[y[1]];
			msz[x] = max(msz[x], sz[y[1]]);
		}
	}
}

int get_center(int x) {
	dfn.clear();
	dfs(x);
	pi ret{int(1e9), -1};
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		ret = min(ret, pi{w, x});
	}
	return ret[1];
}

lint sum[MAXN], f[MAXN], g[MAXN];
vector<pi> todo;
vector<array<lint, 3>> thedownwardspiral;

void dfs_get_size(int x, int p = -1) {
	sz[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (y == p || vis[y])
			continue;
		dfs_get_size(y, x);
		sz[x] += sz[y];
	}
}

pi stk[MAXN]; // decreasing
int stksize;
int changes[MAXN];

void dfs_fill(int x, int p = -1, int subs = -1, lint curmin = 0) {
	if (curmin > sum[x]) {
		thedownwardspiral.push_back({sum[x], subs == -1 ? x : subs, sz[x]});
		curmin = sum[x];
	}
	changes[x] = 0;
	todo.push_back({x, subs == -1 ? x : subs});
	for (auto &[w, y] : gph[x]) {
		if (y == p || vis[y])
			continue;
		sum[y] = sum[x] + w;
		f[y] = max(f[x], sum[y]);
		g[y] = max(g[x] + w, 0ll);
		dfs_fill(y, x, subs == -1 ? y : subs, curmin);
	}
}

void dfs_stack_change(int x, int p = -1) {
	int opos = -1;
	pi oval;
	int osize = stksize;
	{
		int s = 0, e = stksize;
		while (s != e) {
			int m = (s + e) / 2;
			if (stk[m][0] > sum[x])
				s = m + 1;
			else
				e = m;
		}
		if (s > 0)
			changes[x] = changes[stk[s - 1][1]] + 1;
		else
			changes[x] = 0;
		opos = s;
		oval = stk[s];
		stk[s] = pi{sum[x], x};
		stksize = s + 1;
	}
	for (auto &[w, y] : gph[x]) {
		if (y == p || vis[y])
			continue;
		dfs_stack_change(y, x);
	}
	stksize = osize;
	stk[opos] = oval;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
	}
	queue<int> que;
	que.push(0);
	vector<pi> ans(n);
	vector<vector<pi>> foo2(n);
	vector<vector<lint>> sum2(n);
	vector<lint> sumsumsum(n);
	while (sz(que)) {
		auto x = que.front();
		que.pop();
		x = get_center(x);
		todo.clear();
		thedownwardspiral.clear();
		f[x] = g[x] = sum[x] = 0;
		dfs_get_size(x);
		dfs_fill(x);
		dfs_stack_change(x);
		vector<int> ioot = {x};
		for (auto &[w, y] : gph[x]) {
			if (!vis[y])
				ioot.push_back(y);
		}
		{
			vector<pi> foo1;
			for (auto &[falls, sub2, subcnt] : thedownwardspiral) {
				foo1.push_back({falls, subcnt});
				foo2[sub2].push_back({falls, subcnt});
			}
			sort(all(foo1));
			vector<lint> sums(sz(foo1) + 1);
			for (int i = 0; i < sz(foo1); i++) {
				sums[i + 1] = sums[i] + foo1[i][1];
			}
			for (auto &x : ioot) {
				sort(all(foo2[x]));
				sum2[x].resize(sz(foo2[x]) + 1);
				sum2[x][0] = 0;
				for (int i = 0; i < sz(foo2[x]); i++) {
					sum2[x][i + 1] = sum2[x][i] + foo2[x][i][1];
				}
			}
			for (auto &[v, sub1] : todo) {
				if (sub1 != x)
					ans[v][1] += 1ll * changes[v] * (sz[x] - sz[sub1]);

				int j1 = lower_bound(all(foo1), pi{-f[v], -1}) - foo1.begin();
				ans[v][1] += sums[j1];

				int j2 = lower_bound(all(foo2[sub1]), pi{-f[v], -1}) - foo2[sub1].begin();
				ans[v][1] -= sum2[sub1][j2];
			}
			foo1.clear();
			for (auto &w : ioot)
				foo2[w].clear();

			lint sumsum = 0;
			for (auto &y : todo) {
				foo1.push_back({g[y[0]] - sum[y[0]], 0});
				foo2[y[1]].push_back({g[y[0]] - sum[y[0]], 0});
				sumsum += sum[y[0]];
				sumsumsum[y[1]] += sum[y[0]];
			}
			sort(all(foo1));
			sums.resize(sz(foo1) + 1);
			sums[0] = 0;
			for (int i = 0; i < sz(foo1); i++) {
				sums[i + 1] = sums[i] + foo1[i][0];
			}
			for (auto &x : ioot) {
				sort(all(foo2[x]));
				sum2[x].resize(sz(foo2[x]) + 1);
				sum2[x][0] = 0;
				for (int i = 0; i < sz(foo2[x]); i++) {
					sum2[x][i + 1] = sum2[x][i] + foo2[x][i][0];
				}
			}

			for (auto &x : todo) {
				int j1 = lower_bound(all(foo1), pi{f[x[0]], -1}) - foo1.begin();

				ans[x[0]][0] += sums.back() - sums[j1];
				ans[x[0]][0] += 1ll * j1 * f[x[0]];
				ans[x[0]][0] += sumsum;

				int j2 = lower_bound(all(foo2[x[1]]), pi{f[x[0]], -1}) - foo2[x[1]].begin();

				ans[x[0]][0] -= sum2[x[1]].back() - sum2[x[1]][j2];
				ans[x[0]][0] -= 1ll * j2 * f[x[0]];
				ans[x[0]][0] -= sumsumsum[x[1]];
			}
		}
		for (auto &w : ioot) {
			foo2[w].clear();
			sumsumsum[w] = 0;
		}
		vis[x] = 1;
		for (auto &y : gph[x]) {
			if (!vis[y[1]]) {
				que.push(y[1]);
			}
		}
	}
	cout << "1\n";
	for (int i = 0; i < n; i++)
		cout << ans[i][0] << " ";
	cout << "\n";
	for (int i = 0; i < n; i++)
		cout << ans[i][1] << " ";
	cout << "\n";
}