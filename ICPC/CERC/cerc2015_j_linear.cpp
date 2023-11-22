#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = array<int, 2>;
using lint = long long;
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
		int cc = 0;
		for (int i = 0; i < sz(gph); i++) {
			if (!dfn[i]) {
				dfs(i, -1);
			}
		}
		vector<array<int, 3>> counts(sz(gph));
		for (int i = 0; i < sz(gph); i++) {
			counts[disj.find(i)][0]++;
			counts[d2.find(i)][1]++;
			counts[d3.find(i)][2]++;
		}
		lint ans = 0;
		for (int i = 0; i < sz(gph); i++) {
			ans += counts[i][0] * (counts[i][0] - 1) / 2;
			ans += counts[i][1] * (counts[i][1] - 1) / 2;
			ans += counts[i][2] * (counts[i][2] - 1) / 2;
		}
		cout << ans << "\n";
	}
} tcc;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	tcc.init(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (u != v)
			tcc.add_edge(u - 1, v - 1);
	}
	tcc.solve();
}