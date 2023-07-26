#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXT = 270000;
vector<int> gph[MAXN];
int sz[MAXN], chn[MAXN], din[MAXN], dout[MAXN], piv;
int par[20][MAXN], dep[MAXN];
vector<pi> stk[MAXN];

int lca(int u, int v) {
	if (u == -1 || v == -1)
		return max(u, v);
	if (dep[u] < dep[v])
		swap(u, v);
	int dx = dep[u] - dep[v];
	for (int i = 0; dx; i++) {
		if (dx & 1) {
			u = par[i][u];
		}
		dx >>= 1;
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
}

struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

struct seg {
	int tree[MAXT], lim;
	void init(vector<int> a) {
		for (lim = 1; lim <= sz(a); lim <<= 1)
			;
		for (int i = 0; i < sz(a); i++) {
			tree[i + lim] = a[i];
		}
		for (int i = lim - 1; i; i--)
			tree[i] = lca(tree[2 * i], tree[2 * i + 1]);
	}
	int query(int s, int e) {
		s += lim;
		e += lim;
		int ret = -1;
		while (s < e) {
			if (s % 2 == 1)
				ret = lca(ret, tree[s++]);
			if (e % 2 == 0)
				ret = lca(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e)
			ret = lca(ret, tree[s]);
		return ret;
	}
} lcas;
void prune(int x) {
	sz[x] = 1;
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		par[0][y] = x;
		dep[y] = dep[x] + 1;
		prune(y);
		sz[x] += sz[y];
	}
	sort(all(gph[x]), [&](int a, int b) { return sz[a] > sz[b]; });
}

void dfs(int x) {
	din[x] = ++piv;
	if (sz(gph[x])) {
		chn[gph[x][0]] = chn[x];
		dfs(gph[x][0]);
	}
	for (int i = 1; i < sz(gph[x]); i++) {
		chn[gph[x][i]] = gph[x][i];
		dfs(gph[x][i]);
	}
	dout[x] = piv;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	prune(0);
	dfs(0);
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
	vector<int> indices(m);
	for (auto &x : indices) {
		cin >> x;
		x--;
	}
	vector<vector<pi>> queries(m);
	vector<int> ans(q);
	lcas.init(indices);
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		queries[r].push_back({l, i});
		int vtx = lcas.query(l, r);
		ans[i] -= dep[vtx];
	}
	for (int i = 0; i < m; i++) {
		int d = dep[indices[i]];
		for (int j = indices[i]; d; j = par[0][chn[j]]) {
			int c = chn[j];
			int thres = dep[par[0][c]];
			while (sz(stk[c]) && stk[c].back()[0] <= d) {
				int u = thres + 1;
				int v = stk[c].back()[0];
				int l = stk[c].back()[1];
				stk[c].pop_back();
				bit.add(l, -(v - u + 1));
				bit.add(i, v - u + 1);
				thres = v;
			}
			int u = thres + 1;
			int v = d;
			int l = (sz(stk[c]) ? stk[c].back()[1] : -1);
			if (l != -1) {
				bit.add(l, -(v - u + 1));
			}
			bit.add(i, v - u + 1);
			stk[c].push_back({d, i});
			d = dep[par[0][c]];
		}
		for (auto &[l, idx] : queries[i])
			ans[idx] += bit.query(MAXN - 2) - bit.query(l - 1);
	}
	for (int i = 0; i < q; i++) {
		cout << (ans[i] + 1) << "\n";
	}
}