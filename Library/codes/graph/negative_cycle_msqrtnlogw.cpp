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

vector<vector<pi>> gph;
vector<int> vis, par, pae;

void dfs(int x) {
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (!vis[y]) {
			par[y] = x;
			pae[y] = w;
			dfs(y);
		}
	}
}

vector<lint> solve(int n, vector<array<lint, 3>> edges) {
	vector<lint> p(n);
	auto cost = [&](array<lint, 3> edges) { return edges[2] + p[edges[0]] - p[edges[1]]; };
	while (true) {
		scc.init(n);
		for (auto &[s, e, x] : edges) {
			if (cost({s, e, x}) <= 0)
				scc.add_edge(s, e);
		}
		scc.get_scc(n);
		int V = scc.piv;
		vector<vector<pi>> dag(V);
		vector<int> neg(n);
		for (auto &[s, e, x] : edges) {
			if (scc.comp[s] == scc.comp[e] && cost({s, e, x}) < 0) {
				// position 1
				cr(gph, n);
				cr(vis, n);
				cr(par, n);
				cr(pae, n);
				for (auto &[s2, e2, x2] : edges) {
					if (pi{s2, e2} != pi{s, e} && cost({s2, e2, x2}) <= 0) {
						gph[s2].push_back({0, e2});
					}
				}
				dfs(e);
				assert(vis[s]);
				cout << "CYCLE\n";
				vector<int> path;
				for (int j = s; j != e; j = par[j])
					path.push_back(j);
				path.push_back(e);
				path.push_back(s);
				reverse(all(path));
				cout << sz(path) - 1 << "\n";
				for (int i = 0; i < sz(path); i++)
					cout << path[i] << (i + 1 < sz(path) ? " " : "\n");
				exit(0);
			}
			if (scc.comp[s] != scc.comp[e] && cost({s, e, x}) <= 0) {
				if (cost({s, e, x}) < 0)
					neg[e]++;
				dag[scc.comp[s]].push_back({cost({s, e, x}), scc.comp[e]});
			}
		}
		if (count(all(neg), 0) == sz(neg)) {
			// position 2
			return p;
		}
		vector<int> dp(V);
		for (int i = 0; i < V; i++) {
			for (auto &[w, j] : dag[i]) {
				dp[j] = min(dp[j], dp[i] + (int)w);
			}
		}
		int R = -*min_element(all(dp));
		vector<int> counts(R + 1);
		for (int i = 0; i < n; i++) {
			if (neg[i])
				counts[-dp[scc.comp[i]]]++;
		}
		int mxpos = max_element(all(counts)) - counts.begin();
		if (counts[mxpos] >= 5 * R) {
			// position 3
			for (int i = 0; i < n; i++) {
				if (dp[scc.comp[i]] <= -mxpos)
					p[i]--;
			}
			continue;
		}
		cr(gph, n);
		cr(vis, n);
		cr(par, n);
		cr(pae, n);
		for (auto &[s, e, x] : edges) {
			lint c = cost({s, e, x});
			if (c > 0)
				continue;
			if (dp[scc.comp[e]] == dp[scc.comp[s]] + c) {
				gph[s].push_back({c, e});
			}
		}
		for (int i = 0; i < n; i++) {
			if (!vis[i] && dp[scc.comp[i]] == 0) {
				par[i] = -1;
				dfs(i);
			}
		}
		vector<array<int, 3>> path;
		for (int i = 0; i < n; i++) {
			if (dp[scc.comp[i]] == -R) {
				for (int j = i; dp[scc.comp[j]] < 0; j = par[j]) {
					path.push_back({par[j], j, pae[j]});
				}
				reverse(all(path));
				break;
			}
		}
		assert(sz(path));
		vector<int> phi(n, R), chk(n), par(n, -1);
		int w = R;
		for (int i = 0; i < sz(path); i++) {
			if (path[i][2] == -1) {
				w--;
				phi[path[i][1]] = w;
				chk[path[i][1]] = 1;
			}
		}
		vector<vector<pi>> ogph(n);
		for (auto &[s, e, x] : edges) {
			ogph[s].push_back({max(cost({s, e, x}), 0ll), e});
		}
		vector<queue<int>> que(R + 1);
		for (int i = 0; i < n; i++) {
			que[phi[i]].push(i);
		}
		for (int i = 0; i <= R; i++) {
			while (sz(que[i])) {
				auto v = que[i].front();
				que[i].pop();
				if (phi[v] != i)
					continue;
				for (auto &[d, w] : ogph[v]) {
					if (phi[w] > phi[v] + d) {
						phi[w] = phi[v] + d;
						par[w] = v;
						que[phi[w]].push(w);
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			p[i] += phi[i];
		}
		for (auto &v : edges) {
			if (cost(v) < 0 && chk[v[1]]) {
				// position 4
				vector<int> cyc;
				for (int j = v[0]; j != -1; j = par[j])
					cyc.push_back(j);
				reverse(all(cyc));
				cyc.push_back(v[1]);
				bool pathin = false;
				for (auto &[s, e, x] : path) {
					if (s == v[1]) {
						pathin = true;
					}
					if (pathin)
						cyc.push_back(e);
					if (e == cyc[0])
						break;
				}
				cout << "CYCLE\n";
				cout << sz(cyc) - 1 << "\n";
				for (int i = 0; i < sz(cyc); i++)
					cout << cyc[i] << (i + 1 < sz(cyc) ? " " : "\n");
				exit(0);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	lint wmax = 0;
	vector<array<lint, 3>> edges(m);
	for (auto &[s, e, x] : edges) {
		cin >> s >> e >> x;
		wmax = max(wmax, -x);
	}
	vector<lint> p(n);
	if (wmax > 0) {
		int l = 0;
		while ((2 << l) <= wmax)
			l++;
		for (int j = l; j >= 0; j--) {
			vector<array<lint, 3>> new_edges;
			for (auto &[s, e, x] : edges) {
				lint nx = x + p[s] - p[e];
				if (nx <= -(1 << j)) {
					assert(nx > -(2 << j));
					nx = -1;
				} else {
					nx = (nx + (1ll << j) - 1) / (1ll << j);
				}
				new_edges.push_back({s, e, nx});
			}
			auto newpot = solve(n, new_edges);
			for (int i = 0; i < n; i++)
				p[i] += newpot[i] * (1ll << j);
		}
	}
	vector<vector<pi>> gph(n);
	for (auto &[s, e, x] : edges) {
		assert(x + p[s] - p[e] >= 0);
		gph[s].push_back({x + p[s] - p[e], e});
	}
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	vector<lint> dist(n, 1e18);
	auto enq = [&](int x, lint v) {
		if (dist[x] > v) {
			dist[x] = v;
			pq.push({v, x});
		}
	};
	enq(s, 0);
	while (sz(pq)) {
		auto x = pq.top();
		pq.pop();
		if (dist[x[1]] != x[0])
			continue;
		for (auto &[w, y] : gph[x[1]])
			enq(y, w + x[0]);
	}
	cout << "PATH\n";
	for (int i = 0; i < n; i++)
		cout << dist[i] + p[i] - p[s] << " ";
}
