#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;

vector<int> gph[MAXN], ord;
int par[MAXN];

void dfs(int x) {
	ord.push_back(x);
	for (auto &y : gph[x]) {
		gph[y].erase(find(all(gph[y]), x));
		par[y] = x;
		dfs(y);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	dfs(0);
	reverse(all(ord));
	vector<pi> dp(n), pdp(n);
	vector<int> onboy(n);
	for (auto &x : ord) {
		dp[x] = {0, 1};
		for (auto &y : gph[x]) {
			dp[x][0] += dp[y][0];
			if (dp[y][1])
				dp[x][1] = 0, onboy[x]++;
		}
		if (dp[x][1])
			dp[x][0]++;
	}
	reverse(all(ord));
	for (auto &x : ord) {
		if (x == 0)
			continue;
		pdp[x] = {0, 1};
		pdp[x][0] += dp[par[x]][0] - dp[x][0] - dp[par[x]][1];
		if (onboy[par[x]] - dp[x][1] > 0)
			pdp[x][1] = 0;
		pdp[x][0] += pdp[par[x]][0];
		if (pdp[par[x]][1])
			pdp[x][1] = 0;
		if (pdp[x][1])
			pdp[x][0]++;
	}
	int base = dp[0][0], must = 0;
	for (int i = 0; i < n; i++) {
		int cur = pdp[i][0];
		for (auto &j : gph[i]) {
			cur += dp[j][0];
		}
		if (base > cur)
			must++;
	}
	cout << 1ll * n * (n - 1) / 2 - 1ll * must * (must - 1) / 2 << "\n";
}