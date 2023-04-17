#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

struct strongly_connected {
	vector<vector<int>> gph;

	void init(int n) {
		gph.clear();
		gph.resize(n);
	}

	void add_edge(int s, int e) { gph[s].push_back(e); }

	vector<int> val, comp, z, cont;
	int Time, ncomps;
	template <class G, class F> int dfs(int j, G &g, F f) {
		int low = val[j] = ++Time, x;
		z.push_back(j);
		for (auto e : g[j])
			if (comp[e] < 0)
				low = min(low, val[e] ?: dfs(e, g, f));

		if (low == val[j]) {
			do {
				x = z.back();
				z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while (x != j);
			f(cont);
			cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	template <class G, class F> void scc(G &g, F f) {
		int n = sz(g);
		val.assign(n, 0);
		comp.assign(n, -1);
		Time = ncomps = 0;
		for (int i = 0; i < n; i++)
			if (comp[i] < 0)
				dfs(i, g, f);
	}

	int piv;
	void get_scc(int n) {
		scc(gph, [&](vector<int> &v) {});
		for (int i = 0; i < n; i++) {
			comp[i] = ncomps - comp[i] - 1;
		}
		piv = ncomps;
	}
} scc;

bool vis[MAXN];
vector<pi> gph[MAXN];
vector<lint> a;

vector<pi> src, snk;

void dfs(int x, int p, lint d = 0) {
	snk.push_back({d, x});
	if (a[x] - d >= 0)
		src.push_back({a[x] - d, x});
	for (auto &[w, y] : gph[x]) {
		if (y == p || vis[y])
			continue;
		dfs(y, x, d + w);
	}
}

int sz[MAXN], msz[MAXN];
vector<int> dfn;

void dfsc(int x, int p) {
	sz[x] = 1;
	msz[x] = 0;
	dfn.push_back(x);
	for (auto &[_, y] : gph[x]) {
		if (y == p || vis[y])
			continue;
		dfsc(y, x);
		sz[x] += sz[y];
		msz[x] = max(msz[x], sz[y]);
	}
}

int get_center(int x) {
	dfn.clear();
	dfsc(x, -1);
	pi ret{int(1e9), -1};
	for (auto &y : dfn) {
		int w = max(msz[y], sz(dfn) - sz[y]);
		ret = min(ret, {w, y});
	}
	return ret[1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n;
	cin >> n;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	for (int i = 0; i < n - 1; i++) {
		lint u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({w, v});
		gph[v].push_back({w, u});
	}
	queue<int> que;
	que.push(0);
	int nvtx = n;
	vector<pi> edges;
	auto addEdge = [&](int u, int v) { edges.push_back({u, v}); };
	while (sz(que)) {
		auto x = que.front();
		que.pop();
		x = get_center(x);
		src.clear();
		snk.clear();
		dfs(x, -1);
		sort(all(src));
		sort(all(snk));
		for (int i = 0; i < sz(snk); i++) {
			if (i + 1 < sz(snk))
				addEdge(nvtx + i + 1, nvtx + i);
			addEdge(nvtx + i, snk[i][1]);
		}
		int j = 0;
		for (int i = 0; i < sz(src); i++) {
			while (j < sz(snk) && snk[j][0] <= src[i][0]) {
				j++;
			}
			if (j)
				addEdge(src[i][1], nvtx + j - 1);
		}
		nvtx += sz(snk);
		vis[x] = 1;
		for (auto &[_, y] : gph[x]) {
			if (!vis[y])
				que.push(y);
		}
	}
	scc.init(nvtx);
	for (auto &[u, v] : edges)
		scc.add_edge(u, v);
	scc.get_scc(nvtx);
	vector<int> relevant(scc.piv);
	for (int i = 0; i < n; i++) {
		relevant[scc.comp[i]] = 1;
	}
	vector<pi> ne;
	for (auto &[u, v] : edges) {
		if (scc.comp[u] != scc.comp[v]) {
			ne.push_back({scc.comp[u], scc.comp[v]});
		}
	}
	sort(all(ne));
	for (auto &[u, v] : ne)
		relevant[v] |= relevant[u];
	reverse(all(ne));
	vector<int> route(scc.piv);
	int piv = 0;
	for (int i = 0; i < scc.piv; i++) {
		if (relevant[i])
			route[i] = piv, piv++;
	}
	vector<int> ans(n);
	const int B = 4096;
	vector<bitset<B>> dp(piv);
	for (int i = 0; i < n; i += B) {
		for (int j = i; j < min(n, i + B); j++) {
			dp[route[scc.comp[j]]].set(j - i);
		}
		for (auto &[u, v] : ne) {
			if (relevant[u] && relevant[v])
				dp[route[u]] |= dp[route[v]];
		}
		for (int i = 0; i < n; i++) {
			ans[i] += dp[route[scc.comp[i]]].count();
		}
		for (int i = 0; i < piv; i++)
			dp[i] = 0;
	}
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << "\n";
}