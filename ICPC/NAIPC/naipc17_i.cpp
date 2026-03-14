#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

const int MAXN = 100005;
namespace dtree {

vector<int> E[MAXN], RE[MAXN], rdom[MAXN];

int S[MAXN], RS[MAXN], cs;
int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN], up[MAXN];

void clear(int n) {
	cs = 0;
	for (int i = 0; i <= n; i++) {
		par[i] = val[i] = sdom[i] = rp[i] = dom[i] = S[i] = RS[i] = 0;
		E[i].clear();
		RE[i].clear();
		rdom[i].clear();
	}
}
void add_edge(int x, int y) { E[x].push_back(y); }
void Union(int x, int y) { par[x] = y; }
int Find(int x, int c = 0) {
	if (par[x] == x)
		return c ? -1 : x;
	int p = Find(par[x], 1);
	if (p == -1)
		return c ? par[x] : val[x];
	if (sdom[val[x]] > sdom[val[par[x]]])
		val[x] = val[par[x]];
	par[x] = p;
	return c ? p : val[x];
}
void dfs(int x) {
	RS[S[x] = ++cs] = x;
	par[cs] = sdom[cs] = val[cs] = cs;
	for (int e : E[x]) {
		if (S[e] == 0)
			dfs(e), rp[S[e]] = S[x];
		RE[S[e]].push_back(S[x]);
	}
}
int solve(int s, int *up) { // Calculate idoms
	dfs(s);
	for (int i = cs; i; i--) {
		for (int e : RE[i])
			sdom[i] = min(sdom[i], sdom[Find(e)]);
		if (i > 1)
			rdom[sdom[i]].push_back(i);
		for (int e : rdom[i]) {
			int p = Find(e);
			if (sdom[p] == i)
				dom[e] = i;
			else
				dom[e] = p;
		}
		if (i > 1)
			Union(i, rp[i]);
	}
	for (int i = 2; i <= cs; i++)
		if (sdom[i] != dom[i])
			dom[i] = dom[dom[i]];
	for (int i = 2; i <= cs; i++)
		up[RS[i]] = RS[dom[i]];
	return cs;
}
} // namespace dtree

vector<int> gph[MAXN];
int par[18][MAXN], din[MAXN], dout[MAXN], dep[MAXN], piv;
int table[2 * MAXN];
pi spt[18][2 * MAXN];

bool in(int u, int v) { return din[u] <= din[v] && dout[v] <= dout[u]; }

int lca(int u, int v) {
	if (din[u] > din[v])
		swap(u, v);
	if (in(u, v))
		return u;
	int lg = table[din[v] - dout[u]];
	return min(spt[lg][dout[u]], spt[lg][din[v] - (1 << lg)])[1];
}

vector<pi> seq;

void dfs(int x) {
	din[x] = sz(seq);
	for (auto &y : gph[x]) {
		seq.push_back({dep[x], x});
		dep[y] = dep[x] + 1;
		dfs(y);
		seq.push_back({dep[x], x});
	}
	dout[x] = sz(seq);
}
#define rend fuick

int clz_imp[MAXN], in_imp[MAXN];
vector<int> comp[MAXN];
bool in_query[MAXN];
int parc[MAXN], paec[MAXN], lend[MAXN], rend[MAXN];
int apar[MAXN];

void dfs_fill(int x, int val = -1) {
	apar[x] = x;
	if (in_imp[x])
		val = x;

	clz_imp[x] = val;
	lend[x] = piv;
	if (in_query[x])
		piv++;
	for (auto &y : comp[x]) {
		parc[y] = x;
		paec[y] = dep[y] - dep[x];
		dfs_fill(y, val);
	}
	rend[x] = piv;
}

int apchuk(int x, int th) {
	if (apar[x] != x)
		return apar[x] = apchuk(apar[x], th);
	if (in(x, th))
		return x;
	paec[x] = 0;
	return apar[x] = apchuk(parc[x], th);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for (int i = 1; i < 2 * MAXN; i++) {
		table[i] = table[i - 1];
		while ((2 << table[i]) <= i)
			table[i]++;
	}
	int n, m, q;
	cin >> n >> m >> q;
	vector<pi> todo;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		dtree::add_edge(u, v);
		todo.push_back({u, v});
	}
	dtree::solve(1, par[0]);
	for (int i = 2; i <= n; i++) {
		gph[par[0][i]].push_back(i);
	}
	dfs(1);
	for (int i = 0; i < sz(seq); i++)
		spt[0][i] = seq[i];
	for (int i = 1; i < 18; i++) {
		for (int j = 0; j + (1 << i) <= sz(seq); j++) {
			spt[i][j] = min(spt[i - 1][j], spt[i - 1][j + (1 << (i - 1))]);
		}
	}
	vector<int> imp;
	for (auto &[u, v] : todo) {
		if (par[0][v] != u) {
			imp.push_back(u);
			imp.push_back(v);
		}
	}
	sort(all(imp));
	imp.resize(unique(all(imp)) - imp.begin());
	vector<vector<int>> adj(sz(imp), vector<int>(sz(imp)));
	for (int i = 0; i < sz(imp); i++)
		adj[i][i] = 1, in_imp[imp[i]] = 1;
	for (auto &[u, v] : todo) {
		if (par[0][v] != u) {
			int uc = lower_bound(all(imp), u) - imp.begin();
			int vc = lower_bound(all(imp), v) - imp.begin();
			adj[uc][vc] = 1;
		}
	}
	for (int i = 0; i < sz(imp); i++) {
		for (int j = 0; j < sz(imp); j++) {
			if (in(imp[i], imp[j]))
				adj[i][j] = 1;
		}
	}
	for (int i = 0; i < sz(imp); i++) {
		for (int j = 0; j < sz(imp); j++) {
			for (int k = 0; k < sz(imp); k++) {
				adj[j][k] |= (adj[j][i] & adj[i][k]);
			}
		}
	}
	auto compress = [&](vector<int> v) {
		sort(all(v), [&](int a, int b) { return din[a] < din[b]; });
		auto w = v;
		for (int i = 0; i < sz(v) - 1; i++) {
			w.push_back(lca(v[i], v[i + 1]));
		}
		v = w;
		sort(all(v), [&](int a, int b) { return din[a] < din[b]; });
		v.resize(unique(all(v)) - v.begin());
		for (int i = 0; i < sz(v); i++)
			comp[v[i]].clear();
		vector<int> stk;
		for (auto &x : v) {
			while (sz(stk) && !in(stk.back(), x))
				stk.pop_back();
			if (sz(stk))
				comp[stk.back()].push_back(x);
			stk.push_back(x);
		}
		return v;
	};
	while (q--) {
		int k, l;
		cin >> k >> l;
		vector<int> vlist(l);
		for (auto &x : vlist)
			cin >> x;
		for (auto &x : vlist)
			in_query[x] = 1;
		for (int i = 0; i < sz(imp); i++)
			vlist.push_back(imp[i]);
		auto new_list = compress(vlist);
		vlist.resize(sz(vlist) - sz(imp));
		paec[new_list[0]] = dep[new_list[0]] + 1;
		piv = 0;
		dfs_fill(new_list[0]);
		for (auto &x : vlist) {
			if (clz_imp[x] == -1)
				continue;
			int idx = lower_bound(all(imp), clz_imp[x]) - imp.begin();
			for (int j = 0; j < sz(imp); j++) {
				if (!in(imp[j], x) && adj[j][idx]) {
					// slow
					apchuk(imp[j], x);
				}
			}
		}
		vector<lint> dp(piv + 1);
		dp[0] = 1;
		for (int i = 0; i < k; i++) {
			vector<lint> nxt(piv + 1);
			for (auto &w : new_list) {
				int l = lend[w];
				int r = rend[w];
				if (l == r)
					continue;
				// bcout << w << " " << l << " " << r << " " << paec[w] << endl;
				nxt[r] += dp[l] * paec[w];
			}
			swap(dp, nxt);
		}
		cout << dp[piv] << "\n";
		for (auto &x : vlist)
			in_query[x] = 0;
	}
}