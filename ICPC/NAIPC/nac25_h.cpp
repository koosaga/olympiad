#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 200005;

vector<lint> a;
vector<vector<int>> gph;
vector<int> ord;

void dfs(int x) {
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		dfs(y);
	}
	ord.push_back(x);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	cr(gph, n);
	cr(a, n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	for (auto &i : ord) {
		lint sum = max(0ll, a[i]);
		for (auto &j : gph[i])
			sum += max(0ll, a[j]);
		if (sum > k) {
			cout << "-1\n";
			return 0;
		}
	}
	vector<pi> dp(n); // (placed, total)
	for (auto &i : ord) {
		for (auto &j : gph[i]) {
			dp[i][1] += dp[j][1];
			dp[i][0] += dp[j][0];
		}
		if (dp[i][0] > k) {
			dp[i][1] -= dp[i][0] - k;
			dp[i][0] = k;
		}
		if (a[i] == -1) {
			dp[i][0] = k - dp[i][0];
			dp[i][1] += dp[i][0];
		} else {
			if (dp[i][0] > k - a[i]) {
				dp[i][1] -= dp[i][0] - (k - a[i]);
				dp[i][0] = k - a[i];
			}
			dp[i][0] = a[i];
			dp[i][1] += a[i];
		}
	}
	cout << dp[0][1] << "\n";
}