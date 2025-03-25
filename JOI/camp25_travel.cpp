#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 600006;

array<int, 3> nodes[MAXN];
int pa[MAXN], par[20][MAXN], dep[MAXN];
int nxt[20][MAXN];

int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	vector<array<int, 3>> edges;
	auto g = [&](int u, int v) { return u * m + v; };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (j + 1 < m) {
				edges.push_back({max(a[i][j], a[i][j + 1]), g(i, j), g(i, j + 1)});
			}
			if (i + 1 < n) {
				edges.push_back({max(a[i][j], a[i + 1][j]), g(i, j), g(i + 1, j)});
			}
			nodes[g(i, j)] = {a[i][j], -1, -1};
		}
	}
	iota(pa, pa + n * m * 2, 0);
	sort(all(edges));
	{
		int i = 0;
		for (auto &[w, u, v] : edges) {
			u = find(u);
			v = find(v);
			if (u == v)
				continue;
			pa[u] = n * m + i;
			pa[v] = n * m + i;
			nodes[n * m + i] = {w, u, v};
			par[0][u] = n * m + i;
			par[0][v] = n * m + i;
			i++;
		}
	}
	par[0][2 * n * m - 2] = 2 * n * m - 2;
	for (int i = 2 * n * m - 3; i >= 0; i--)
		dep[i] = dep[par[0][i]] + 1;
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < 2 * n * m - 1; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	auto lca = [&](int u, int v) {
		if (dep[u] > dep[v])
			swap(u, v);
		int d = dep[v] - dep[u];
		for (int i = 0; d; i++) {
			if (d & 1) {
				v = par[i][v];
			}
			d >>= 1;
		}
		if (u == v)
			return u;
		for (int i = 19; i >= 0; i--) {
			if (par[i][u] != par[i][v]) {
				u = par[i][u];
				v = par[i][v];
			}
		}
		return par[0][u];
	};
	for (int i = 0; i <= 2 * n * m - 2; i++) {
		int cur = i, thr = nodes[i][0] + k;
		for (int j = 19; j >= 0; j--) {
			if (dep[cur] >= (1 << j) && nodes[par[j][cur]][0] <= thr) {
				cur = par[j][cur];
			}
		}
		nxt[0][i] = cur;
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < 2 * n * m - 1; j++) {
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int src = g(a - 1, b - 1);
		int dst = g(c - 1, d - 1);
		dst = lca(src, dst);
		if (nodes[nxt[19][src]][0] < nodes[dst][0]) {
			cout << "-1\n";
			continue;
		}
		int ans = 1;
		for (int i = 18; i >= 0; i--) {
			if (nodes[nxt[i][src]][0] < nodes[dst][0]) {
				src = nxt[i][src];
				ans += (1 << i);
			}
		}
		cout << ans << "\n";
	}
}