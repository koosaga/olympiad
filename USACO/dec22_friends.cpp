#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
set<int> gph[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(69);
	int n, m;
	cin >> n >> m;
	vector<int> idx(n);
	iota(all(idx), 0);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (u > v)
			swap(u, v);
		u--;
		v--;
		gph[u].insert(v);
	}
	lint ret = 0;
	for (int i = 0; i < n; i++) {
		ret += sz(gph[idx[i]]);
		if (sz(gph[idx[i]]) == 0)
			continue;
		int j = *gph[idx[i]].begin();
		gph[idx[i]].erase(j);
		int u = idx[i], v = idx[j];
		if(sz(gph[u]) > sz(gph[v])){
			swap(u, v);
		}
		for(auto &x : gph[u]) gph[v].insert(x);
		idx[i] = idx[j] = v;
	}
	cout << ret - m << "\n";
}