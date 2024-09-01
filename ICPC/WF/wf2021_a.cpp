#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1000005;
bool vis[MAXN];
vector<int> gph[MAXN], rev[MAXN];

void dfs(int x, vector<vector<int>> &ans) {
	if (vis[x])
		return;
	vis[x] = 1;
	ans[x / sz(ans[0])][x % sz(ans[0])] = 1;
	for (auto &y : gph[x])
		dfs(y, ans);
}

void dfs2(int x, vector<vector<int>> &ans) {
	if (vis[x])
		return;
	vis[x] = 1;
	ans[x / sz(ans[0])][x % sz(ans[0])] = 0;
	for (auto &y : rev[x])
		dfs2(y, ans);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> ans(n, vector<int>(m, -1));
	while (q--) {
		int dx, dy, b;
		cin >> dx >> dy >> b;
		dx *= -1;
		dy *= -1;
		vector<vector<int>> ok(n, vector<int>(m));
		for (int i = 0; i < b; i++) {
			int x, y;
			cin >> x >> y;
			ok[x - 1][y - 1] = 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (ok[i][j]) {
					ans[i][j] = 1;
					if (i + dx < 0 || i + dx >= n || j + dy < 0 || j + dy >= m)
						continue;
					ans[i + dx][j + dy] = 0;
				} else {
					if (i + dx < 0 || i + dx >= n || j + dy < 0 || j + dy >= m) {
						ans[i][j] = 0;
						continue;
					}
					int l = i * m + j;
					int r = (i + dx) * m + (j + dy);
					gph[l].push_back(r);
					rev[r].push_back(l);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans[i][j] == 1 && !vis[i * m + j])
				dfs(i * m + j, ans);
		}
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans[i][j] == 0 && !vis[i * m + j])
				dfs2(i * m + j, ans);
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << (ans[j][i] != 1 ? '.' : '#');
		}
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << (ans[j][i] == 0 ? '.' : '#');
		}
		cout << "\n";
	}
}