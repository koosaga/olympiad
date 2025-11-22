#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 90005;

lint ccw(pi a, pi b) { return a[0] * b[1] - b[0] * a[1]; }

vector<int> gph[MAXN];
int sum[MAXN];
int n, s;
void dfs(int x) {
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		sum[y] = sum[x] + ccw(pi{x / n, x % n}, pi{y / n, y % n});
		dfs(y);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s;
	set<pi> edges;
	for (int i = 0; i < n * n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
		edges.insert({u, v});
		edges.insert({v, u});
	}
	dfs(0);
	vector<pi> ans;
	auto get_area = [&](int u, int v) { return abs(sum[u] - sum[v] - ccw(pi{v / n, v % n}, pi{u / n, u % n})) / 2; };
	for (int i = 0; i < n * n; i++) {
		if (i % n + 1 < n) {
			if (edges.count({i, i + 1}) == 0) {
				auto ga = get_area(i, i + 1);
				if (ga == s)
					ans.push_back({i, i + 1});
			}
		}
		if (i + n < n * n) {
			if (edges.count({i, i + n}) == 0) {
				auto ga = get_area(i, i + n);
				if (ga == s)
					ans.push_back({i, i + n});
			}
		}
	}
	cout << sz(ans) << "\n";
	if (sz(ans) == 0)
		ans.push_back({-1, -1});
	ans.resize(1);
	for (auto &[x, y] : ans)
		cout << x + 1 << " " << y + 1 << "\n";
}