
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 400005;

vector<int> gph[MAXN];
vector<int> dfn;
int sz[MAXN], msz[MAXN], vis[MAXN];

void dfs(int x, int p = -1) {
	dfn.push_back(x);
	sz[x] = 1, msz[x] = 0;
	for (auto &y : gph[x]) {
		if (y != p && !vis[y]) {
			dfs(y, x);
			sz[x] += sz[y];
			msz[x] = max(msz[x], sz[y]);
		}
	}
}

int get_center(int x) {
	dfn.clear();
	dfs(x);
	pi ret{int(1e9), -1};
	for (auto &x : dfn) {
		int w = max(sz(dfn) - sz[x], msz[x]);
		ret = min(ret, pi{w, x});
	}
	return ret[1];
}

int a[MAXN];

struct node1 {
	int idx, len, done, subidx;
};

struct node2 {
	int need, len, subidx;
};

vector<node1> A;
vector<node2> B;

void dfs1(int x, int p, int source, int needLength = 1e9, int length = 0) {
	needLength = min(needLength - 1, a[x]);
	A.push_back({x, length, needLength <= 0, source});
	for (auto &y : gph[x]) {
		if (!vis[y] && y != p) {
			dfs1(y, x, (p == -1 ? y : source), needLength, length + 1);
		}
	}
}

void dfs2(int x, int p, int source, int needLength = 1e9, int length = 0) {
	needLength = min(needLength, a[x] - length);
	B.push_back({needLength, length, source});
	for (auto &y : gph[x]) {
		if (!vis[y] && y != p) {
			dfs2(y, x, (p == -1 ? y : source), needLength, length + 1);
		}
	}
}

int n, d;

void solve(vector<int> &ans, vector<node1> A, vector<node2> B, int sgn) {
	int m = 0;
	for (auto &x : A) {
		m = max(m, 1 + x.len);
	}
	vector<int> bylen(m), dx(m + 1);
	for (auto &p2 : B) {
		if (d - p2.len >= 0)
			bylen[min(m - 1, d - p2.len)]++;
		int lb = p2.need;
		int ub = d - p2.len;
		lb = max(lb, 0);
		ub = min(ub, m - 1);
		if (lb <= ub) {
			dx[lb]++;
			dx[ub + 1]--;
		}
	}
	for (int i = 1; i <= m; i++)
		dx[i] += dx[i - 1];
	for (int i = m - 2; i >= 0; i--)
		bylen[i] += bylen[i + 1];
	for (auto &p1 : A) {
		if (p1.done) {
			ans[p1.idx] += bylen[p1.len] * sgn;
		} else {
			ans[p1.idx] += dx[p1.len] * sgn;
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> d;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		sort(all(gph[i]));
	}
	queue<int> que;
	que.push(0);
	vector<int> ans(n);
	while (sz(que)) {
		int c = que.front();
		que.pop();
		c = get_center(c);
		{
			A.clear();
			B.clear();
			dfs1(c, -1, c);
			dfs2(c, -1, c);
			solve(ans, A, B, +1);
			vector<vector<node1>> AG(sz(gph[c]));
			vector<vector<node2>> BG(sz(gph[c]));
			for (auto &p1 : A) {
				if (p1.subidx != c) {
					p1.subidx = lower_bound(all(gph[c]), p1.subidx) - gph[c].begin();
					AG[p1.subidx].push_back(p1);
				}
			}
			for (auto &p1 : B) {
				if (p1.subidx != c) {
					p1.subidx = lower_bound(all(gph[c]), p1.subidx) - gph[c].begin();
					BG[p1.subidx].push_back(p1);
				}
			}
			for (int i = 0; i < sz(gph[c]); i++) {
				if (sz(AG[i]))
					solve(ans, AG[i], BG[i], -1);
			}
		}
		vis[c] = 1;
		for (auto &d : gph[c]) {
			if (!vis[d])
				que.push(d);
		}
	}
	for (auto &x : ans)
		cout << x << "\n";
}