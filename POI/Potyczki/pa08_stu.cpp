#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

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

bool negative_cycle(int n, vector<array<int, 3>> edges) {
	vector<lint> dist(n);
	for (int i = 0; i < n + 1; i++) {
		bool upd = false;
		for (auto &[u, v, w] : edges) {
			if (dist[v] > dist[u] + w) {
				upd = 1;
				dist[v] = dist[u] + w;
			}
		}
		if (!upd)
			return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<array<int, 3>> edges(m);
	scc.init(n);
	for (auto &[u, v, w] : edges) {
		cin >> u >> v >> w;
		u--;
		v--;
		w *= -1;
		scc.add_edge(u, v);
	}
	scc.get_scc(n);
	vector<vector<int>> vlist(scc.piv);
	vector<vector<array<int, 3>>> elist(scc.piv);
	for (int i = 0; i < n; i++) {
		vlist[scc.comp[i]].push_back(i);
	}
	for (auto &[u, v, w] : edges) {
		if (scc.comp[u] == scc.comp[v]) {
			int l = lower_bound(all(vlist[scc.comp[u]]), u) - vlist[scc.comp[u]].begin();
			int r = lower_bound(all(vlist[scc.comp[u]]), v) - vlist[scc.comp[u]].begin();
			elist[scc.comp[u]].push_back({l, r, w});
		}
	}
	vector<int> vtx;
	for (int i = 0; i < scc.piv; i++) {
		if (negative_cycle(sz(vlist[i]), elist[i])) {
			for (auto &j : vlist[i])
				vtx.push_back(j);
		}
	}
	sort(all(vtx));
	cout << sz(vtx) << "\n";
	for (auto &i : vtx)
		cout << i + 1 << " ";
}
