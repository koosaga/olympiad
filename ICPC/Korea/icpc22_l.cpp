#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

vector<int> gph[MAXN];
int vis[MAXN], dep[MAXN], par[MAXN];
vector<pi> lenseq[MAXN];

void dfs(int x, int p = -1) {
	vis[x] = 1;
	for (auto &y : gph[x]) {
		if (y != p && !vis[y]) {
			vis[y] = 1;
			dep[y] = dep[x] + 1;
			par[y] = x;
			dfs(y, x);
		} else if (dep[y] < dep[x]) {
			lenseq[dep[x] - dep[y]].push_back({x, y});
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < 2 * n - 3; i++) {
		int u, v;
		cin >> u >> v;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	for (int i = 2; i <= n; i++) {
		if (sz(lenseq[i]) >= 2) {
			cout << i + 1 << "\n";
			for (int j = 0; j < 2; j++) {
				int p = lenseq[i][j][0];
				int v = lenseq[i][j][1];
				for (int k = p; k != v; k = par[k])
					cout << k << " ";
				cout << v << "\n";
			}
			return 0;
		}
	}
	cout << "3\n";
	{
		int p = lenseq[2][0][0];
		int v = lenseq[2][0][1];
		for (int k = p; k != v; k = par[k])
			cout << k << " ";
		cout << v << "\n";
	}
	{
		int a = lenseq[n - 1][0][0];
		int b = lenseq[n - 1][0][1];
		int c = lenseq[n - 2][0][0];
		if (a == c)
			c = lenseq[n - 2][0][1];
		cout << a << " " << b << " " << c << "\n";
	}
}