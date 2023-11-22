#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<int, 2>;

struct disj {
	vector<int> pa;
	void init(int n) {
		pa.clear();
		pa.resize(n);
		iota(all(pa), 0);
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
} disj, d2, d3;

struct tcc {
	vector<vector<pi>> gph;
	vector<int> dfn, dout, low, deg;
	int ts, piv;
	void init(int n) {
		ts = piv = 0;
		gph.clear();
		dfn.clear();
		low.clear();
		deg.clear();
		dout.clear();
		gph.resize(n);
		dfn.resize(n);
		low.resize(n);
		deg.resize(n);
		dout.resize(n);
		disj.init(n);
		d2.init(n);
		d3.init(n);
	}
	void add_edge(int u, int v) {
		assert(u != v);
		gph[u].push_back({ts, v});
		gph[v].push_back({ts, u});
		d3.uni(u, v);
		ts++;
	}
	vector<int> dfs(int x, int p) {
		dfn[x] = low[x] = piv++;
		vector<int> ret;
		auto collapse = [&](vector<int> &v, int y = -1) {
			while (sz(v)) {
				auto bk = v.back();
				if (y != -1 && !(dfn[bk] <= dfn[y] && dfn[y] < dout[bk]))
					break;
				v.pop_back();
				disj.uni(bk, x);
				deg[x] += deg[bk] - 2;
			}
		};
		for (auto &[i, y] : gph[x]) {
			if (i == p) {
				deg[x]++;
				continue;
			}
			if (!dfn[y]) {
				auto rec = dfs(y, i);
				if (low[y] > dfn[x])
					continue;
				d2.uni(y, x);
				deg[x]++;
				if (sz(rec) && deg[rec.back()] == 2)
					rec.pop_back();
				if (low[y] < low[x]) {
					low[x] = low[y];
					swap(rec, ret);
				}
				collapse(rec);
			} else {
				deg[x]++;
				if (dfn[y] > dfn[x]) {
					collapse(ret, y);
					deg[x] -= 2;
				} else if (dfn[y] < low[x]) {
					low[x] = dfn[y];
					collapse(ret);
				}
			}
		}
		dout[x] = piv;
		ret.push_back(x);
		return ret;
	}
	void solve() {
		for (int i = 0; i < sz(gph); i++) {
			if (!dfn[i]) {
				dfs(i, -1);
			}
		}
	}
} tcc;

vector<int> dfn, low;
vector<vector<pi>> gph;
vector<vector<int>> bcc, cmp;

int piv;

void dfs(int x, int p) {
	dfn[x] = low[x] = piv++;
	for (auto &[i, y] : gph[x]) {
		if (i == p)
			continue;
		if (!dfn[y]) {
			dfs(y, i);
			low[x] = min(low[x], low[y]);
		} else
			low[x] = min(low[x], dfn[y]);
	}
}
void color(int x, int p) {
	if (p) {
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for (auto &[_, i] : gph[x]) {
		if (cmp[i].size())
			continue;
		if (low[i] >= dfn[x]) {
			bcc.push_back({x});
			int c = sz(bcc) - 1;
			cmp[x].push_back(c);
			color(i, c);
		} else
			color(i, p);
	}
}

namespace solver {
const int MAXN = 200005;
struct edge {
	int pos, cst, idx;
};

vector<edge> gph[MAXN];
int din[MAXN], dout[MAXN], dep[MAXN], par[MAXN], pae[MAXN], piv;
lint HS[MAXN];
vector<int> backs, ord;
struct disj D;

void dfs(int x, int p) {
	ord.push_back(x);
	din[x] = ++piv;
	for (auto &y : gph[x]) {
		if (y.idx == p)
			continue;
		if (!din[y.pos]) {
			par[y.pos] = x;
			pae[y.pos] = y.idx;
			dep[y.pos] = dep[x] + 1;
			dfs(y.pos, y.idx);
		} else if (din[x] < din[y.pos]) {
			backs.push_back(y.idx);
		}
	}
	dout[x] = ++piv;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

int pinf0[MAXN];
int pinf1[MAXN];
int pinf2[MAXN];
int pa[MAXN];

int paint(int *arr, int u, int v, int i) {
	if (pa[u] != u)
		return pa[u] = paint(arr, pa[u], v, i);
	if (din[u] <= din[v] && dout[v] <= dout[u])
		return u;
	arr[u] = i;
	return pa[u] = paint(arr, par[u], v, i);
}

map<lint, lint> m1, m2;

lint dfs2(int x, vector<lint> &H, vector<array<int, 3>> &edges) {
	lint ans = 0;
	for (auto &y : gph[x]) {
		if (y.idx != pae[y.pos])
			continue;
		if (pinf0[y.pos] != -1) {
			ans += 1ll * m1[H[pae[y.pos]] ^ H[pinf0[y.pos]]] * edges[pinf0[y.pos]][2] * edges[pae[y.pos]][2];
		}
		ans += 1ll * m2[H[pae[y.pos]]] * edges[pae[y.pos]][2];
		m1[H[pae[y.pos]]] += edges[pae[y.pos]][2];
		if (pinf1[y.pos] != -1) {
			m2[H[pae[y.pos]] ^ H[pinf1[y.pos]]] += 1ll * edges[pinf1[y.pos]][2] * edges[pae[y.pos]][2];
			if (pinf2[y.pos] != pinf1[y.pos])
				m2[H[pae[y.pos]] ^ H[pinf2[y.pos]]] += 1ll * edges[pinf2[y.pos]][2] * edges[pae[y.pos]][2];
		}
		ans += dfs2(y.pos, H, edges);
		m1[H[pae[y.pos]]] -= edges[pae[y.pos]][2];
		if (pinf1[y.pos] != -1) {
			m2[H[pae[y.pos]] ^ H[pinf1[y.pos]]] -= 1ll * edges[pinf1[y.pos]][2] * edges[pae[y.pos]][2];
			if (pinf2[y.pos] != pinf1[y.pos])
				m2[H[pae[y.pos]] ^ H[pinf2[y.pos]]] -= 1ll * edges[pinf2[y.pos]][2] * edges[pae[y.pos]][2];
		}
	}
	return ans;
}

lint solve(vector<int> vertices, vector<array<int, 3>> edges) {
	/*{
		lint ans = 0;
		for (int i = 0; i < sz(edges); i++) {
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < j; k++) {
					for (auto &x : vertices)
						D.pa[x] = x;
					int com = sz(vertices) - 1;
					for (int x = 0; x < sz(edges); x++) {
						if (x == i || x == j || x == k)
							continue;
						com -= D.uni(edges[x][0], edges[x][1]);
					}
					if (com)
						ans += 1ll * edges[i][2] * edges[j][2] * edges[k][2];
				}
			}
		}
		// return ans;
	}*/
	if (sz(vertices) == 1)
		return 0;
	for (auto &x : vertices) {
		din[x] = dout[x] = dep[x] = piv = 0;
		pinf0[x] = pinf1[x] = pinf2[x] = -1;
		HS[x] = 0;
		gph[x].clear();
		D.pa[x] = x;
	}
	ord.clear();
	backs.clear();
	vector<lint> H(sz(edges));
	for (int i = 0; i < sz(edges); i++) {
		//	assert(find(all(vertices), edges[i][0]) != vertices.end());
		//	assert(find(all(vertices), edges[i][1]) != vertices.end());
		gph[edges[i][0]].push_back({edges[i][1], edges[i][2], i});
		gph[edges[i][1]].push_back({edges[i][0], edges[i][2], i});
		H[i] = randint(0, (1ll << 62) - 1);
	}
	dfs(vertices[0], -1);
	for (auto &i : backs) {
		if (din[edges[i][0]] > din[edges[i][1]])
			swap(edges[i][0], edges[i][1]);
		HS[edges[i][0]] ^= H[i];
		HS[edges[i][1]] ^= H[i];
	}
	reverse(all(ord));
	for (auto &x : ord) {
		if (x == vertices[0])
			break;
		H[pae[x]] = HS[x];
		HS[par[x]] ^= HS[x];
	}
	sort(all(backs), [&](const int &a, const int &b) { return dep[edges[a][0]] > dep[edges[b][0]]; });
	for (auto &x : vertices)
		pa[x] = x;
	for (auto &i : backs) {
		paint(pinf0, edges[i][1], edges[i][0], i);
	}
	sort(all(backs), [&](const int &a, const int &b) { return din[edges[a][1]] < din[edges[b][1]]; });
	for (auto &x : vertices)
		pa[x] = x;
	for (auto &i : backs) {
		paint(pinf1, edges[i][1], edges[i][0], i);
	}
	sort(all(backs), [&](const int &a, const int &b) { return dout[edges[a][1]] > dout[edges[b][1]]; });
	for (auto &x : vertices)
		pa[x] = x;
	for (auto &i : backs) {
		paint(pinf2, edges[i][1], edges[i][0], i);
	}
	map<lint, int> count_back;
	for (auto &x : backs) {
		count_back[H[x]] += edges[x][2];
	}
	// one tree edges
	lint ans = 0;
	for (auto &x : vertices) {
		if (pinf0[x] == -1) {
			continue;
		}
		ans += 1ll * edges[pinf0[x]][2] * edges[pae[x]][2] * count_back[H[pae[x]] ^ H[pinf0[x]]];
	}
	m1.clear();
	m2.clear();
	// two tree edges
	pae[vertices[0]] = -1;
	ans += dfs2(vertices[0], H, edges);
	// three tree edges
	for (auto &z : backs) {
		D.uni(edges[z][0], edges[z][1]);
	}
	vector<int> nv;
	vector<array<int, 3>> ne;
	for (auto &z : vertices) {
		if (D.find(z) == z)
			nv.push_back(z);
	}
	for (auto &[u, v, w] : edges) {
		u = D.find(u);
		v = D.find(v);
		if (u != v)
			ne.push_back({u, v, w});
	}
	ans += solve(nv, ne);
	return ans;
}
}; // namespace solver

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	tcc.init(n);
	vector<pi> edges(m);
	for (auto &[u, v] : edges) {
		cin >> u >> v;
		u--;
		v--;
		tcc.add_edge(u, v);
	}
	tcc.solve();
	solver::D.init(n);
	// assume graph is connected
	// case 1: bridges
	lint ans = 0;
	{
		int m = sz(edges);
		for (auto &[u, v] : edges) {
			if (d2.find(u) != d2.find(v)) {
				m--;
				ans += 1ll * m * (m - 1) / 2;
			}
		}
		// case 2: cactus cuts
		cr(dfn, n);
		cr(low, n);
		cr(gph, n);
		cr(cmp, n);
		cr(bcc, 1);
		int c = 0;
		for (auto &[u, v] : edges) {
			if (d2.find(u) == d2.find(v) && disj.find(u) != disj.find(v)) {
				gph[disj.find(u)].push_back({c, disj.find(v)});
				gph[disj.find(v)].push_back({c, disj.find(u)});
				c++;
			}
		}
		for (int i = 0; i < n; i++) {
			if (d2.find(i) == i) {
				int j = disj.find(i);
				dfs(j, -1);
				color(j, 0);
			}
		}
		for (int i = 1; i < sz(bcc); i++) {
			int z = sz(bcc[i]);
			ans += (1ll * z * (z - 1) / 2) * (m - z);
			ans += (1ll * z * (z - 1) * (z - 2) / 6);
		}
		vector<vector<array<int, 3>>> comp(n);
		vector<vector<array<int, 3>>> cycleEdges(n);
		vector<vector<int>> vtx(n);
		for (auto &[u, v] : edges) {
			if (d2.find(u) == d2.find(v)) {
				if (disj.find(u) != disj.find(v)) {
					//	assert(sz(cmp[disj.find(u)]));
					//	assert(sz(cmp[disj.find(v)]));

					int uh = cmp[disj.find(u)][0];
					int vh = cmp[disj.find(v)][0];
					int s = sz(bcc[max(uh, vh)]);
					//	assert(find(all(bcc[max(uh, vh)]), disj.find(u)) != bcc[max(uh, vh)].end());
					//	assert(find(all(bcc[max(uh, vh)]), disj.find(v)) != bcc[max(uh, vh)].end());

					cycleEdges[disj.find(u)].push_back({max(uh, vh), u, s});
					cycleEdges[disj.find(v)].push_back({max(uh, vh), v, s});
				} else {
					comp[disj.find(u)].push_back({u, v, 1});
				}
			}
		}
		for (int i = 0; i < n; i++)
			vtx[disj.find(i)].push_back(i);
		for (int i = 0; i < n; i++) {
			if (disj.find(i) == i) {
				sort(all(cycleEdges[i]));
				assert(sz(cycleEdges[i]) % 2 == 0);
				for (int j = 0; j < sz(cycleEdges[i]); j += 2) {
					int u = cycleEdges[i][j][1];
					int v = cycleEdges[i][j + 1][1];
					int c = cycleEdges[i][j][2];
					if (u != v)
						comp[i].push_back({u, v, c});
				}
				ans += solver::solve(vtx[i], comp[i]);
			}
		}
	}
	cout << ans << "\n";
}