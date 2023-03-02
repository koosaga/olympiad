#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

int par[18][MAXN], dep[MAXN];
vector<int> gph[MAXN];

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1)
			v = par[i][v];
		dx >>= 1;
	}
	for (int i = 17; i >= 0; i--) {
		if (par[i][u] != par[i][v]) {
			u = par[i][u];
			v = par[i][v];
		}
	}
	if (u == v)
		return u;
	return par[0][v];
}

int dist(int u, int v) { return dep[u] + dep[v] - dep[lca(u, v)] * 2; }

struct disj {
	int pa[MAXN];
	pi info[MAXN];
	void init(int n) {
		iota(pa, pa + n, 0);
		for (int i = 0; i < n; i++) {
			pa[i] = i;
			info[i][1] = i;
		}
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	void uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return;
		pa[q] = p;
		info[p][0] = max(info[p][0], info[q][0] + dist(p, q));
	}
} disj;

void dfs(int x, int p) {
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			par[0][y] = x;
			dfs(y, x);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u = a[u - 1] - 1;
		v = a[v - 1] - 1;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0, -1);
	for (int i = 1; i < 18; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	disj.init(n);
	for (int i = 1; i < n; i++) {
		for (auto &j : gph[i]) {
			if (i > j)
				disj.uni(i, j);
		}
	}
	cout << disj.info[n - 1][0] << "\n";
}
