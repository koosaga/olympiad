#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> gph(n);
	vector<int> c(n);
	for (int i = 0; i < n; i++) {
		c[i] = randint(0, 3);
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	auto conf = [&](int v) {
		int cnt = 0;
		for (auto &w : gph[v]) {
			if (c[w] == c[v])
				cnt++;
		}
		return cnt;
	};
	queue<int> que;
	for (int i = 0; i < n; i++) {
		if (conf(i) >= 2)
			que.push(i);
	}
	while (sz(que)) {
		int x = que.front();
		que.pop();
		if (conf(x) < 2)
			continue;
		int cnt[4] = {};
		for (auto &y : gph[x]) {
			cnt[c[y]]++;
		}
		c[x] = min_element(cnt, cnt + 4) - cnt;
		for (auto &y : gph[x]) {
			if (conf(y) >= 2)
				que.push(y);
		}
	}
	for (auto &x : c)
		cout << x + 1 << " ";
}