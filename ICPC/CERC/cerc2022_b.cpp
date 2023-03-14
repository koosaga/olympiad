#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 1557, MAXM = 1557;

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

int solve(vector<int> forb, int v) {
	bpm.clear();
	vector<int> chk(v);
	for (auto &x : forb)
		chk[x] = 1;
	for (int i = 0; i < v; i++) {
		int pcnt = __builtin_popcount(i);
		if (chk[i] || pcnt % 2 == 1)
			continue;
		for (int j = 0; (1 << j) < v; j++) {
			if (chk[i ^ (1 << j)])
				continue;
			bpm.add_edge(i, i ^ (1 << j));
		}
	}
	return bpm.match(v);
}

// if all max matching contains S -> Alice wins
// if exists max matching without S -> Bob wins

string solve(int s, vector<int> forb, int v) {
	int m1 = solve(forb, v);
	forb.push_back(s);
	int m2 = solve(forb, v);
	return m1 != m2 ? "Alice" : "Bob";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;
		int S = 0;
		vector<int> forb(m);
		{
			string s, t;
			cin >> s >> t;
			for (int i = 0; i < n; i++) {
				if (s[i] != t[i])
					S |= (1 << i);
			}
		}
		for (auto &i : forb) {
			string s;
			cin >> s;
			for (int j = 0; j < n; j++) {
				if (s[j] == '.')
					i |= (1 << j);
			}
		}
		cout << solve(S, forb, 1 << n) << "\n";
	}
}