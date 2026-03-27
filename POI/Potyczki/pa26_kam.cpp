#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

struct dsu {
	vector<vector<int>> whoin;
	vector<int> pa;
	void init(int n) {
		cr(pa, n);
		cr(whoin, n);
		for (int i = 0; i < n; i++) {
			pa[i] = i;
			whoin[i].push_back(i);
		}
	}
	bool uni(int u, int v) {
		u = pa[u];
		v = pa[v];
		if (u == v)
			return false;
		if (sz(whoin[u]) < sz(whoin[v]))
			swap(u, v);
		for (auto &x : whoin[v]) {
			pa[x] = u;
			whoin[u].push_back(x);
		}
		return true;
	}
	int find(int x) { return pa[x]; }
} dsu;

int pcomp(vector<int> &pa, int x) { return pa[x] = (pa[x] == x ? x : pcomp(pa, pa[x])); }

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> colors(n);
	vector<vector<int>> gph(n);
	vector<map<int, int>> mp(n);
	for (auto &x : colors)
		cin >> x, x--;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	vector<int> counts(k);
	vector<int> amuna(k);
	for (int i = 0; i < n; i++) {
		counts[colors[i]]++;
		amuna[colors[i]] = i;
	}
	dsu.init(n);
	queue<int> que;
	for (int i = 0; i < k; i++) {
		if (counts[i] == 1) {
			que.push(i);
		}
	}
	auto uni_and_update = [&](int i, int j) {
		if (colors[i] == -1 || colors[j] == -1)
			return;
		// cout << i << " " << colors[i] << " " << j << " " << colors[j] << endl;
		assert(colors[i] == colors[j]);
		if (dsu.uni(i, j)) {
			counts[colors[i]]--;
			if (counts[colors[i]] == 1)
				que.push(colors[i]);
		}
	};
	for (int i = 0; i < n; i++) {
		for (auto &j : gph[i]) {
			if (colors[i] == colors[j])
				uni_and_update(i, j);
		}
	}
	vector<int> pa(n, -1);
	auto find = [&](int x) { return pcomp(pa, x); };
	auto uni = [&](int p, int q) {
		p = find(p);
		q = find(q);
		if (p == q)
			return false;
		if (sz(mp[p]) < sz(mp[q]))
			swap(p, q);
		for (auto &[k, v] : mp[q]) {
			if (mp[p].count(k)) {
				uni_and_update(mp[p][k], v);
			}
			mp[p][k] = v;
		}
		pa[q] = p;
		return true;
	};
	while (sz(que)) {
		int x = que.front();
		que.pop();
		//	cout << "proc color " << x << endl;
		x = dsu.find(amuna[x]);
		for (auto &y : dsu.whoin[x]) {
			pa[y] = y;
			colors[y] = -1;
			for (auto &z : gph[y]) {
				if (colors[z] != -1) {
					if (mp[y].count(colors[z])) {
						uni_and_update(mp[y][colors[z]], z);
					}
					mp[y][colors[z]] = z;
				}
			}
		}
		for (auto &y : dsu.whoin[x]) {
			for (auto &z : gph[y]) {
				if (colors[z] == -1)
					uni(y, z);
			}
			// find neighbors to uni
		}
		{
			// asserts
			set<int> s;
			for (auto &y : dsu.whoin[x]) {
				s.insert(find(y));
			}
			assert(sz(s) == 1);
		}
	}
	if (*max_element(all(counts)) > 1) {
		cout << "NIE\n";
	} else
		cout << "TAK\n";
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}