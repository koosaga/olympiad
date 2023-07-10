#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 50005;
int par[16][MAXN], dep[MAXN];
vector<int> gph[MAXN];

struct disj {
	int pa[MAXN];
	void init(int n) {
		for (int i = 0; i < n; i++)
			pa[i] = i;
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

void dfs(int x, int p = -1) {
	for (auto &y : gph[x]) {
		if (y != p) {
			dep[y] = dep[x] + 1;
			par[0][y] = x;
			dfs(y, x);
		}
	}
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(u, v);
	int dx = dep[v] - dep[u];
	for (int i = 0; dx; i++) {
		if (dx & 1)
			v = par[i][v];
		dx >>= 1;
	}
	if (u == v)
		return u;
	for (int i = 15; i >= 0; i--) {
		if (par[i][u] != par[i][v]) {
			u = par[i][u];
			v = par[i][v];
		}
	}
	return par[0][u];
}

bool ok(int i1, int j1, int i2, int j2) {
	int l = lca(j1, j2);
	return max(dep[i1], dep[i2]) <= dep[l];
}
bool insec(pi a, pi b) {
	int l0 = lca(a[0], a[1]);
	int l1 = lca(b[0], b[1]);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (ok(l0, a[i], l1, b[j]))
				return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pi> be;
	disj.init(n);
	for (int i = 0; i < n + 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (disj.uni(u, v)) {
			gph[u].push_back(v);
			gph[v].push_back(u);
		} else {
			be.push_back({u, v});
		}
	}
	dfs(0);
	for (int i = 1; i < 16; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	auto pairwise = [&](vector<pi> p) {
		for (int i = 0; i < sz(p); i++) {
			for (int j = 0; j < i; j++) {
				if (insec(p[i], p[j]))
					return false;
			}
		}
		return true;
	};
	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		int ans = 1;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				vector<pi> paths;
				paths.push_back({u, be[i][j]});
				paths.push_back({be[i][j ^ 1], v});
				if (pairwise(paths))
					ans++;
			}
		}
		for (int i = 0; i < 2; i++) {
			swap(be[0], be[1]);
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					vector<pi> paths;
					paths.push_back({u, be[0][j]});
					paths.push_back({be[0][j ^ 1], be[1][k]});
					paths.push_back({be[1][k ^ 1], v});
					if (pairwise(paths))
						ans++;
				}
			}
		}
		cout << ans << "\n";
	}
}
