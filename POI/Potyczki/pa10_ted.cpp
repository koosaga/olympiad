#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<int, 2>;

vector<vector<pi>> gph;
vector<int> endsAt, vis, vis2;
vector<int> que;
bool fucked = 0;

void dfs(int x, int p, int m) {
	vis[x] = 1;
	for (auto &[i, y] : gph[x]) {
		if (y == p || i >= m)
			continue;
		if (endsAt[y] < i && endsAt[x] < i) {
			fucked = 1;
		}
		if (endsAt[y] < i || endsAt[x] < i) {
			que.push_back(i);
		}
		dfs(y, x, m);
	}
}

bool prop(int x, int p, int m) {
	if (vis2[x])
		return true;
	vis2[x] = 1;
	for (auto &[i, y] : gph[x]) {
		if (y == p || i >= m)
			continue;
		if (endsAt[y] < i)
			return false;
		if (!prop(y, x, m))
			return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<pi> edges(n - 1);
	for (auto &[u, v] : edges) {
		cin >> u >> v;
		u--;
		v--;
	}
	endsAt.resize(n);
	vis.resize(n);
	vis2.resize(n);
	int ans = 1e9;
	for (int i = 0; i < 2; i++) {
		gph.clear();
		gph.resize(n);
		fill(all(endsAt), 1e9);
		for (int j = 0; j < n - 1; j++) {
			if (j % 2 == i) {
				gph[edges[j][0]].push_back({j, edges[j][1]});
				gph[edges[j][1]].push_back({j, edges[j][0]});
			} else {
				endsAt[edges[j][0]] = min(endsAt[edges[j][0]], j);
				endsAt[edges[j][1]] = min(endsAt[edges[j][1]], j);
			}
		}
		auto trial = [&](int m) {
			fill(all(vis), 0);
			fill(all(vis2), 0);
			for (int i = 0; i < n; i++) {
				if (!vis[i]) {
					fucked = 0;
					que.clear();
					dfs(i, -1, m);
					if (fucked)
						return false;
					for (auto &x : que) {
						if (endsAt[edges[x][0]] > endsAt[edges[x][1]])
							swap(edges[x][0], edges[x][1]);
						if (!prop(edges[x][1], edges[x][0], m)) {
							fucked = 1;
							break;
						}
					}
					if (fucked)
						return false;
				}
			}
			return true;
		};
		int s = 0, e = n - 1;
		while (s != e) {
			int m = (s + e + 1) / 2;
			if (trial(m))
				s = m;
			else
				e = m - 1;
		}
		ans = min(ans, s + 1);
	}
	if (ans >= n)
		ans = -1;
	cout << ans << "\n";
}