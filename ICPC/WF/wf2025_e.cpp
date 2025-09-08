#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const lint MAXN = 1000000;

const int adj[4][4] = {{1, 1, -1, 0}, {1, 1, -1, 0}, {-1, -1, -1, -1}, {0, 0, 0, 0}};
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> whom(2 * n);
	vector<lint> comp(2 * n);
	vector<array<lint, 4>> code(n);
	for (int i = 0; i < 2 * n; i++) {
		whom[i].push_back(i);
		comp[i] = i;
	}
	unordered_map<lint, int> mp[4];
	vector<int> equals(2 * n);
	auto regen = [&](int p) {
		code[p][0] = comp[2 * p] * MAXN + comp[2 * p];
		code[p][1] = comp[2 * p + 1] * MAXN + comp[2 * p + 1];
		code[p][2] = comp[2 * p] * MAXN + comp[2 * p + 1];
		code[p][3] = comp[2 * p + 1] * MAXN + comp[2 * p];
	};
	lint ans = 0;
	auto ins = [&](int i, int v) {
		if (v == 1) {
			if (comp[2 * i] == comp[2 * i + 1]) {
				equals[comp[2 * i]]++;
				ans += 3 * equals[comp[2 * i]];
			}
			for (int j = 0; j < 4; j++) {
				mp[j][code[i][j]]++;
			}
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					if (adj[j][k] && mp[j].count(code[i][k]))
						ans += adj[j][k] * mp[j][code[i][k]];
				}
			}
		}
		if (v == -1) {
			if (comp[2 * i] == comp[2 * i + 1]) {
				ans -= 3 * equals[comp[2 * i]];
				equals[comp[2 * i]]--;
			}
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					if (adj[j][k] && mp[j].count(code[i][k]))
						ans -= adj[j][k] * mp[j][code[i][k]];
				}
			}
			for (int j = 0; j < 4; j++) {
				mp[j][code[i][j]]--;
			}
		}
	};
	for (int i = 0; i < n; i++) {
		regen(i);
		ins(i, +1);
	}
	auto upd = [&](int p, int c) {
		ins(p / 2, -1);
		comp[p] = c;
		regen(p / 2);
		ins(p / 2, +1);
	};
	auto uni = [&](int u, int v) {
		u = comp[u];
		v = comp[v];
		if (u == v)
			return;
		if (sz(whom[u]) < sz(whom[v]))
			swap(u, v);
		for (auto &k : whom[v]) {
			upd(k, u);
			whom[u].push_back(k);
		}
	};
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		uni(2 * u, 2 * v + 1);
		cout << ans - n << "\n";
	}
}