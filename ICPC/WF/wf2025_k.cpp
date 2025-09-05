#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

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
} dsu;

vector<vector<pi>> gph;
vector<lint> dep;
vector<int> ords;
bool bad = false;
vector<int> vis;

void dfs(int x) {
	vis[x] = 1;
	ords.push_back(x);
	for (auto &[w, y] : gph[x]) {
		if (vis[y]) {
			if (dep[y] != dep[x] + w)
				bad = true;
		} else {
			dep[y] = dep[x] + w;
			dfs(y);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q, tx, ty;
	cin >> n >> m >> q >> tx >> ty;
	tx--;
	ty--;
	cr(gph, n + m);
	dsu.init(n + m);
	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		gph[a].push_back({c, b + n});
		gph[b + n].push_back({-c, a});
		dsu.uni(a, b + n);
	}
	cr(vis, n + m);
	cr(dep, n + m);
	// find for conflicts
	for (int i = 0; i < n + m; i++) {
		if (!vis[i]) {
			dfs(i);
			lint lo = -1e18, hi = 1e18;
			for (auto &z : ords) {
				if (z < n)
					lo = max(lo, dep[z]);
				else
					hi = min(hi, dep[z]);
			}
			if (hi - lo < 0)
				bad = true;

			ords.clear();
		}
	}
	// TODO: extend defn
	if (bad) {
		cout << "impossible\n";
		return 0;
	}
	if (dsu.uni(tx, ty + n)) {
		cr(vis, n + m);
		cr(dep, n + m);
		dfs(tx);
		auto o1 = ords;
		ords.clear();
		dfs(ty + n);
		auto o2 = ords;
		ords.clear();
		lint offset1 = 0, offset2 = 0;
		for (auto &z : o1) {
			if (z < n)
				offset1 = max(offset1, dep[z] - dep[tx]);
		}
		for (auto &z : o2) {
			if (z >= n)
				offset2 = max(offset2, dep[ty + n] - dep[z]);
		}
		cout << offset1 + offset2 << "\n";
		return 0;
	}
	cout << dep[ty + n] - dep[tx] << "\n";
}