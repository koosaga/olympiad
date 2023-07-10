#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 3005;

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

bool is_mst[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<array<int, 5>> edges;
	vector<array<int, 3>> g1, g2;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		if (i < n - 1) {
			g1.push_back({i, u, v});
		}
		edges.push_back({w, (i >= n - 1 ? 0 : -1), u, v, i});
	}
	sort(all(edges));
	disj.init(n);
	for (int i = 0; i < m; i++) {
		if (disj.uni(edges[i][2], edges[i][3])) {
			g2.push_back({edges[i][4], edges[i][2], edges[i][3]});
			is_mst[edges[i][4]] = 1;
		}
	}
	vector<pi> ans;
	while (true) {
		vector<vector<pi>> gph(n);
		disj.init(n);
		vector<array<int, 3>> need_rep;
		for (auto &[i, u, v] : g1) {
			if (is_mst[i])
				disj.uni(u, v);
			else {
				need_rep.push_back({i, u, v});
			}
		}
		if (sz(need_rep) == 0)
			break;
		for (auto &[i, u, v] : need_rep) {
			u = disj.find(u);
			v = disj.find(v);
			gph[u].push_back({i, v});
			gph[v].push_back({i, u});
		}
		for (int i = 0; i < n; i++) {
			if (disj.find(i) == i && sz(gph[i]) == 1) {
				auto across = [&](int u, int v) {
					int x1 = disj.find(u) == disj.find(i);
					int x2 = disj.find(v) == disj.find(i);
					return x1 != x2;
				};
				int tr = -1, ta = -1;
				for (int i = 0; i < sz(g1); i++) {
					if (across(g1[i][1], g1[i][2])) {
						tr = g1[i][0] + 1;
						g1.erase(g1.begin() + i);
						break;
					}
				}
				for (auto &[i, u, v] : g2) {
					if (across(u, v)) {
						ta = i + 1;
						g1.push_back({i, u, v});
						break;
					}
				}
				ans.push_back({tr, ta});
				break;
			}
		}
	}
	cout << sz(ans) << "\n";
	for (auto &[x, y] : ans)
		cout << x << " " << y << "\n";
}
