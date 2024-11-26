#include <bits/stdc++.h>
using namespace std;
using pi = array<long long, 2>;
struct edge {
	int s, e, x, num;
} a[300005];
bool cmp(edge a, edge b) { return a.x < b.x; }

struct disj {
	int pa[100005];
	void init(int n) {
		for (int i = 0; i <= n; i++)
			pa[i] = i;
	}
	int find(int x) {
		if (pa[x] == x)
			return x;
		return pa[x] = find(pa[x]);
	}
	bool uni(int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return 0;
		pa[q] = p;
		return 1;
	}
} disj;

vector<edge> tree;
vector<edge> not_tree;
vector<pi> graph[100005];

int n, m;
long long ret[300005];

int pa[100005][17], pae[100005][17], dep[100005], sz[100005];
int root_val[100005], nxt[100005];

int dfs(int x, int par, int depth) {
	pa[x][0] = nxt[x] = par;
	dep[x] = depth;
	for (int i = 1; i <= 16; i++) {
		pa[x][i] = pa[pa[x][i - 1]][i - 1];
		pae[x][i] = max(pae[pa[x][i - 1]][i - 1], pae[x][i - 1]);
	}
	int r = 1;
	for (int i = 0; i < graph[x].size(); i++) {
		if (graph[x][i][1] == par)
			continue;
		pae[graph[x][i][1]][0] = graph[x][i][0];
		r += dfs(graph[x][i][1], x, depth + 1);
	}
	return sz[x] = r;
}

int lca(int s, int e) {
	if (dep[s] > dep[e])
		swap(s, e);
	int piv = dep[e] - dep[s];
	int ps = s;
	int pe = e;
	for (int i = 0; (1 << i) <= piv; i++) {
		if (piv & (1 << i)) {
			pe = pa[pe][i];
		}
	}
	for (int i = 16; i >= 0; i--) {
		if (pa[ps][i] == 0)
			continue;
		if (pa[ps][i] != pa[pe][i]) {
			ps = pa[ps][i];
			pe = pa[pe][i];
		}
	}
	if (ps != pe) {
		ps = pa[ps][0], pe = pa[pe][0];
	}
	return ps;
}

int pathmax(int v, int u) {
	int dx = dep[v] - dep[u], ans = 0;
	for (int i = 0; dx; i++) {
		if (dx & 1) {
			ans = max(ans, pae[v][i]);
			v = pa[v][i];
		}
		dx >>= 1;
	}
	return ans;
}
int paint(int s, int e, int x) {
	if (dep[s] <= dep[e])
		return s;
	if (!root_val[s])
		root_val[s] = x;
	return nxt[s] = paint(nxt[s], e, x);
}

void solve() {
	for (int i = 0; i < m; i++) {
		if (disj.uni(a[i].s, a[i].e)) {
			tree.push_back(a[i]);
			graph[a[i].s].push_back({a[i].x, a[i].e});
			graph[a[i].e].push_back({a[i].x, a[i].s});
		} else
			not_tree.push_back(a[i]);
	}
	dfs(1, 0, 0);
	for (int i = 0; i < not_tree.size(); i++) {
		int s = not_tree[i].s;
		int e = not_tree[i].e;
		int x = not_tree[i].x + 1;
		int l = lca(s, e);
		int pm = max(pathmax(s, l), pathmax(e, l));
		ret[not_tree[i].num] = (pm < not_tree[i].x ? 3 : 2);
		paint(s, l, x);
		paint(e, l, x);
	}
	for (int i = 0; i < tree.size(); i++) {
		if (pa[tree[i].e][0] != tree[i].s) {
			swap(tree[i].s, tree[i].e);
		}
		int qr = root_val[tree[i].e];
		if (qr == 0 || qr - 1 > tree[i].x)
			ret[tree[i].num] = 1;
		else
			ret[tree[i].num] = 2;
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a[i].s, &a[i].e, &a[i].x);
		a[i].num = i;
	}
	disj.init(n);
	sort(a, a + m, cmp);
	solve();
	for (int i = 0; i < m; i++) {
		printf("%lld\n", ret[i]);
	}
}