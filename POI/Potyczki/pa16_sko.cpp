#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005, MAXM = 200005;

struct dom {
	vector<int> E[MAXN], RE[MAXN], rdom[MAXN];

	int S[MAXN], RS[MAXN], cs;
	int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

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
} dom;

struct bpm {
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
	void clear() {
		for (int i = 0; i < MAXN; i++)
			gph[i].clear();
	}
	void add_edge(int l, int r) { gph[l].push_back(r); }
	bool bfs(int n) {
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for (int i = 0; i < n; i++) {
			if (l[i] == -1 && !dis[i]) {
				que.push(i);
				dis[i] = 1;
			}
		}
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			for (auto &i : gph[x]) {
				if (r[i] == -1)
					ok = 1;
				else if (!dis[r[i]]) {
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x) {
		if (vis[x])
			return 0;
		vis[x] = 1;
		for (auto &i : gph[x]) {
			if (r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))) {
				l[x] = i;
				r[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int match(int n) {
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while (bfs(n)) {
			memset(vis, 0, sizeof(vis));
			for (int i = 0; i < n; i++)
				if (l[i] == -1 && dfs(i))
					ret++;
		}
		return ret;
	}
} bpm;

vector<vector<int>> gph;
vector<int> col;

void dfs(int x, int c) {
	if (col[x])
		return;
	col[x] = c;
	for (auto &y : gph[x]) {
		dfs(y, 3 - c);
	}
}

int par[MAXN];
int sum[MAXN];

void dfs2(int x, vector<int> &chk) {
	sum[x] = chk[x];
	for (auto &y : gph[x]) {
		dfs2(y, chk);
		sum[x] += sum[y];
	}
}

pi solve(int n, vector<pi> edges, vector<int> marks) {
	cr(gph, n);
	dom.clear(n);
	for (auto &[u, v] : edges) {
		// cout << "edge " << u << " " << v << endl;

		dom.add_edge(u + 1, v + 1);
	}
	memset(par, 0, sizeof(par));
	dom.solve(1, par);
	for (int i = 2; i <= n; i++) {
		if (par[i]) {
			//	cout << par[i] << " " << i << endl;
			gph[par[i] - 1].push_back(i - 1);
		}
	}
	dfs2(0, marks);
	pi ans{sum[0], 1ll * sum[0] * sum[0]};
	for (auto &j : gph[0])
		ans[1] -= 1ll * sum[j] * sum[j];
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n;
	cr(gph, n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	cr(col, n);
	for (int i = 0; i < n; i++) {
		if (!col[i]) {
			dfs(i, 1);
		}
	}
	for (int i = 0; i < n; i++) {
		if (col[i] == 1) {
			for (auto &j : gph[i])
				bpm.add_edge(i, j);
		}
	}
	bpm.match(n);
	vector<pi> g1, r1;
	for (int i = 0; i < n; i++) {
		if (col[i] == 1) {
			if (bpm.l[i] == -1) {
				g1.push_back({0, i + 1});
			}
			for (auto &j : gph[i]) {
				if (j == bpm.l[i]) {
					g1.push_back({j + 1, i + 1});
					r1.push_back({i + 1, j + 1});
				} else {
					r1.push_back({j + 1, i + 1});
					g1.push_back({i + 1, j + 1});
				}
			}
		} else {
			if (bpm.r[i] == -1)
				r1.push_back({0, i + 1});
		}
	}
	vector<int> marks(n + 1);
	for (int i = 0; i < n; i++)
		marks[i + 1] = (col[i] == 1);
	auto [L1, P1] = solve(n + 1, g1, marks);
	for (int i = 0; i < n; i++)
		marks[i + 1] = (col[i] == 2);
	auto [L2, P2] = solve(n + 1, r1, marks);
	cout << L1 * L2 + (P1 + P2) / 2 << "\n";
}