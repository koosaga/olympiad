#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;
		vector<lint> a(n);
		for (auto &x : a)
			cin >> x;
		lint ans = 0;
		vector<map<int, lint>> gph(n);
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			gph[u][v] = gph[v][u] = a[u] + a[v];
		}
		queue<int> que;
		for (int i = 1; i < n - 1; i++) {
			if (sz(gph[i]) == 2) {
				que.push(i);
			}
		}
		bool ok = 1;
		while (sz(que)) {
			auto v = que.front();
			que.pop();
			if (sz(gph[v]) != 2)
				continue;
			auto [pv, pw] = *gph[v].begin();
			auto [qv, qw] = *gph[v].rbegin();
			ans += (pw - a[v]) * (qw - a[v]);
			gph[v].clear();
			gph[pv].erase(v);
			gph[qv].erase(v);
			if (gph[pv].count(qv)) {
				gph[pv][qv] = gph[qv][pv] = a[pv] + a[qv];
				ans -= a[pv] * a[qv];
			} else {
				gph[pv][qv] = gph[qv][pv] = pw + qw - a[v];
			}
			for (auto &p : {pv, qv}) {
				if (p > 0 && p < n - 1 && sz(gph[p]) == 2)
					que.push(p);
			}
		}
		for (int i = 1; i < n - 1; i++) {
			if (sz(gph[i])) {
				ok = 0;
			}
		}
		if (ok)
			cout << ans << "\n";
		else
			cout << "bad\n";
	}
}