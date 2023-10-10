#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 1005, MAXM = 1005;
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
	bool chk[MAXN + MAXM];
	void rdfs(int x, int n) {
		if (chk[x])
			return;
		chk[x] = 1;
		for (auto &i : gph[x]) {
			chk[i + n] = 1;
			rdfs(r[i], n);
		}
	}
	vector<int> getcover(int n, int m) { // solve min. vertex cover
		match(n);
		memset(chk, 0, sizeof(chk));
		for (int i = 0; i < n; i++)
			if (l[i] == -1)
				rdfs(i, n);
		vector<int> v;
		for (int i = 0; i < n; i++)
			if (!chk[i])
				v.push_back(i);
		for (int i = n; i < n + m; i++)
			if (chk[i])
				v.push_back(i);
		return v;
	}
} bpm;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> chkA(n), chkB(n);
	vector<vector<int>> gph(n);
	int g = 0;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (u == 0 && v == n - 1) {
			g++;
			continue;
		}
		if (u == 0)
			chkA[v] = 1;
		else if (v == n - 1)
			chkB[u] = 1;
		else
			gph[u].push_back(v);
	}
	for (int i = 0; i < n; i++) {
		if (chkA[i] && chkB[i])
			bpm.add_edge(i, i);
		for (auto &j : gph[i]) {
			if (chkA[i] && chkB[j])
				bpm.add_edge(i, j);
		}
	}
	cout << g + bpm.match(n) << "\n";
}