#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 100005;

vector<int> ord;
vector<int> gph[MAXN];
int sz[MAXN], par[MAXN];

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
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	dfs(0);
	reverse(all(ord));
	vector<lint> dp(n);
	for (auto &x : ord) {
		sz[x] = 1;
		lint sum = 0;
		for (auto &y : gph[x]) {
			auto ret = dp[y];
			sz[x] += sz[y];
			sum += ret + sz[y] - 1ll * sz[y] * sz[y];
		}
		sum += 1ll * (sz[x] - 1) * (sz[x] - 1);
		dp[x] = sum;
	}
	reverse(all(ord));
	vector<lint> pdp(n);
	for (auto &x : ord) {
		lint pars = pdp[x] + (n - sz[x]) - 1ll * (n - sz[x]) * (n - sz[x]);
		for (auto &y : gph[x]) {
			pars += dp[y] + sz[y] - 1ll * sz[y] * sz[y];
		}
		for (auto &y : gph[x]) {
			pdp[y] = pars - (dp[y] + sz[y] - 1ll * sz[y] * sz[y]);
			pdp[y] += 1ll * (n - sz[y] - 1) * (n - sz[y] - 1);
		}
	}
	lint ans = 1e18;
	for (int i = 0; i < n; i++) {
		lint sum = 0;
		sum += pdp[i] + (n - sz[i]) - 1ll * (n - sz[i]) * (n - sz[i]);
		for (auto &j : gph[i]) {
			sum += dp[j] + sz[j] - 1ll * sz[j] * sz[j];
		}
		sum += 1ll * (n - 1) * (n - 1);
		ans = min(ans, sum);
	}
	cout << ans << "\n";
}