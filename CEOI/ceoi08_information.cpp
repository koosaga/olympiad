// Can be made to O(n^3 / 64) using bitset
// Can be made to linear time with http://i.stanford.edu/pub/cstr/reports/cs/tr/74/455/CS-TR-74-455.pdf
// As far as I understand, https://oj.uz/submission/130464 is incorrect.

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<vector<pi>> gph;
vector<int> tr, par, vis, pae;
vector<int> ord;

void dfs1(int x) {
	vis[x] = 1;
	ord.push_back(x);
	for (auto &[i, y] : gph[x]) {
		if (!vis[y] && tr[i] == 0) {
			par[y] = x;
			pae[y] = i;
			tr[i] = 1;
			dfs1(y);
		}
	}
}

void dfs2(int x) {
	vis[x] = 1;
	for (auto &[i, y] : gph[x]) {
		if (!vis[y] && tr[i] == 0) {
			tr[i] = 2;
			dfs2(y);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	cr(gph, n);
	cr(tr, m);
	cr(par, n);
	cr(pae, n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back({i, v});
	}
	cr(vis, n);
	ord.clear();
	dfs1(0);
	if (sz(ord) < n) {
		cout << "NONE\n";
		return 0;
	}
	cr(vis, n);
	dfs2(0);
	while (count(all(vis), 1) < n) {
		int v = -1;
		for (int j = 1; j < sz(ord); j++) {
			if (vis[par[ord[j]]] && !vis[ord[j]]) {
				v = ord[j];
			}
			tr[pae[ord[j]]] = 0;
		}
		tr[pae[v]] = 2;
		cr(vis, n);
		ord.clear();
		dfs1(0);
		if (sz(ord) < n) {
			cout << "NONE\n";
			return 0;
		}
		for (int j = 0; j < m; j++)
			if (tr[j] == 2)
				tr[j] = 0;
		cr(vis, n);
		dfs2(0);
	}
	vector<int> ans[2];
	for (int i = 0; i < m; i++) {
		if (tr[i])
			ans[tr[i] - 1].push_back(i + 1);
	}
	for (int i = 0; i < 2; i++) {
		for (auto &j : ans[i])
			cout << j << " ";
		cout << "\n";
	}
}