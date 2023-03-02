#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 200005;

int n;
string t, s;
vector<int> tr[MAXN], gph[MAXN];
pi dp[MAXN][2];

int idx;

void dfs(int x) {
	s[idx++] = t[x];
	int mine = idx - 1;
	for (auto &y : tr[x]) {
		tr[y].erase(find(all(tr[y]), x));
		gph[mine].push_back(idx);
		dfs(y);
	}
}

pi operator+(const pi &a, const pi &b) { return pi{a[0] + b[0], a[1] + b[1]}; }
map<int, pi> mp;
pi solve(int k) {
	if (mp.count(k))
		return mp[k];
	for (int v = n - 1; v >= 0; v--) {
		dp[v][0] = {0, 0};
		dp[v][1] = {1, 0};
		for (auto &w : gph[v]) {
			if (s[v] != '1')
				dp[v][0] = dp[v][0] + min(dp[w][0], dp[w][1] + pi{k, 1});
			dp[v][1] = dp[v][1] + min(dp[w][0], dp[w][1]);
		}
		if (s[v] == '1')
			dp[v][0] = {lint(1e18), 0};
	}
	return mp[k] = min(dp[0][0], dp[0][1] + pi{k, 1});
}

vector<lint> dap;

void dnc(int l, int r) {
	if (r - l <= 1)
		return;
	int m = (l + r) / 2;
	auto al = solve(l);
	auto ar = solve(r);
	auto am = solve(m);
	lint solL = al[0] + 1ll * (m - l) * al[1];
	lint solR = ar[0] + 1ll * (m - r) * ar[1];
	for (int i = l; i <= r; i++) {
		dap[i] = min(dap[i], am[0] + 1ll * (i - m) * am[1]);
	}
	if (solL != am[0])
		dnc(l, m);
	if (solR != am[0])
		dnc(m, r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> t;
	s = t;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dfs(0);
	dap.resize(n + 1);
	fill(all(dap), 1e18);
	{
		auto ans = solve(1);
		for (int i = 1; i <= n; i++) {
			dap[i] = min(dap[i], ans[0] + 1ll * (i - 1) * ans[1]);
		}
	}
	{
		auto ans = solve(n);
		for (int i = 1; i <= n; i++) {
			dap[i] = min(dap[i], ans[0] + 1ll * (i - n) * ans[1]);
		}
	}
	dnc(1, n);
	for (int k = 1; k <= n; k++)
		cout << dap[k] << "\n";
}