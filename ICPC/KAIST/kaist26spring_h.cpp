#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 1000005;

lint ccw(pi a, pi b, pi c) {
	for (int i = 0; i < 2; i++) {
		b[i] -= a[i], c[i] -= a[i];
	}
	return b[0] * c[1] - b[1] * c[0];
}

vector<vector<pi>> gph, rev;
vector<lint> cst;
vector<int> vis;
vector<pi> coords;
int piv;
int nxt[20][MAXN];

void dfs1(int x) {
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (!vis[y])
			dfs1(y);
	}
	coords[x][0] = piv++;
}

void dfs2(int x) {
	vis[x] = 1;
	for (auto &[w, y] : gph[x]) {
		if (!vis[y])
			dfs2(y);
	}
	coords[x][1] = piv++;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	cr(gph, n);
	cr(rev, n);
	cr(cst, m);
	vector<pi> a(n);
	for (auto &[x, y] : a)
		cin >> x >> y;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		gph[u].push_back({i, v});
		rev[v].push_back({i, u});
		cst[i] = w;
	}
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]), [&](const pi &x, const pi &y) { return ccw(a[i], a[x[1]], a[y[1]]) > 0; });
		sort(all(rev[i]), [&](const pi &x, const pi &y) { return ccw(a[i], a[x[1]], a[y[1]]) > 0; });
	}
	nxt[0][n - 1] = n - 1;
	vector<pi> T1_pinfo(n), T2_pinfo(n);
	vector<lint> T1_route(n), T2_route(n);
	for (int i = 0; i < n; i++) {
		if (i < n - 1) {
			nxt[0][i] = gph[i].back()[1];
			T1_pinfo[i] = pi{gph[i].back()[1], gph[i].back()[0]};
		}
		if (i > 0) {
			T2_pinfo[i] = pi{rev[i][0][1], rev[i][0][0]};
		}
	}
	for (int i = 1; i < 20; i++) {
		for (int j = 0; j < n; j++)
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
	}
	cr(coords, n);
	cr(vis, n);
	dfs1(0);
	for (int i = 0; i < n; i++) {
		reverse(all(gph[i]));
	}
	cr(vis, n);
	piv = 0;
	dfs2(0);
	for (int i = 0; i < n; i++) {
		reverse(all(gph[i]));
	}
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
		coords[i][0] = n - 1 - coords[i][0];
		coords[i][1] = n - 1 - coords[i][1];
		rev[coords[i][0]] = i;
	}
	vector<lint> dem(n);
	auto add_routing = [&](int s, int e, lint x) {
		if (x == 0)
			return;
		assert(s < e);
		if (s >= 0)
			dem[s] += x;
		else
			s = 0;
		if (e < n)
			dem[e] -= x;
		else
			e = n - 1;
		if (s == e)
			return;
		int pi = s;
		for (int i = 19; i >= 0; i--) {
			int totry = nxt[i][pi];
			if (coords[totry][0] <= coords[e][0] && coords[totry][1] <= coords[e][1]) {
				pi = totry;
			}
		}
		T1_route[s] += x;
		T1_route[pi] -= x;
		T2_route[e] += x;
		T2_route[pi] -= x;
	};
	for (int i = 0; i < n; i++) {
		for (auto &[idx, j] : gph[i]) {
			dem[i] += cst[idx];
			dem[j] -= cst[idx];
		}
	}
	map<lint, pi> mp;
	mp[1] = pi{lint(1e18), -1};
	for (auto &v : rev) {
		if (dem[v] < 0) {
			mp[-coords[v][1]] = pi{-dem[v], v};
		}
		if (dem[v] > 0) {
			auto it = mp.lower_bound(-coords[v][1]);
			while (dem[v] > 0) {
				lint dx = min(dem[v], (*it).second[0]);
				add_routing((*it).second[1], v, dx);
				if ((*it).second[0] == dx)
					it = mp.erase(it);
				else {
					auto g = *it;
					mp.erase(it);
					g.second[0] -= dx;
					mp[g.first] = g.second;
				}
			}
		}
	}
	while (sz(mp) > 1) {
		auto g = *mp.begin();
		add_routing(g.second[1], n, g.second[0]);
		mp.erase(mp.begin());
	}
	for (int i = 0; i < n - 1; i++) {
		T1_route[T1_pinfo[i][0]] += T1_route[i];
		cst[T1_pinfo[i][1]] += T1_route[i];
	}
	for (int i = n - 1; i > 0; i--) {
		T2_route[T2_pinfo[i][0]] += T2_route[i];
		cst[T2_pinfo[i][1]] += T2_route[i];
	}
	for (int i = 0; i < m; i++)
		cout << cst[i] << "\n";
}