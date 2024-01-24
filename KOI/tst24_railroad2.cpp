#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int mod = 1e9 + 7;

const int MAXN = 500005;
vector<pi> gph[MAXN];
lint dist[MAXN][2];

pi dfs(int x, int p, int l, lint d = 0) {
	pi ret{d, x};
	dist[x][l] = d;
	for (auto &[w, y] : gph[x]) {
		if (y != p) {
			auto z = dfs(y, x, l, d + w);
			ret = max(ret, z);
		}
	}
	return ret;
}

struct disj {
	int pa[MAXN], sz[MAXN];
	void init(int n) {
		iota(pa, pa + n, 0);
		fill(sz, sz + n, 1);
	}
	int find(int x) { return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	int getsz(int x) { return sz[find(x)]; }
	void uni(int p, int q) {
		p = find(p), q = find(q);
		assert(p != q);
		pa[q] = p;
		sz[p] += sz[q];
	}
} disj;
int travel(vector<int> U, vector<int> V, vector<int> W) {
	int n = sz(U) + 1;
	for (int i = 0; i < n - 1; i++) {
		gph[U[i]].push_back({W[i], V[i]});
		gph[V[i]].push_back({W[i], U[i]});
	}
	int a = dfs(0, -1, 1)[1];
	dist[a][0] = 0;
	int b = dfs(a, -1, 0)[1];
	dist[b][1] = 0;
	dfs(b, -1, 1);
	vector<array<lint, 3>> spans;
	spans.push_back({dist[b][0], a, b});
	for (int i = 0; i < n; i++) {
		if (i != a && i != b) {
			if (dist[i][0] > dist[i][1])
				spans.push_back({dist[i][0], a, i});
			else
				spans.push_back({dist[i][1], b, i});
		}
	}
	sort(all(spans));
	reverse(all(spans));
	disj.init(n);
	lint ans = 0;
	for (auto &[w, u, v] : spans) {
		int l = disj.getsz(u);
		int r = disj.getsz(v);
		ans += (1ll * l * r % mod) * (w % mod) % mod;
		disj.uni(u, v);
	}
	return (ans << 1) % mod;
}