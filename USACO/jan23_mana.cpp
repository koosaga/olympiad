#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 200005;

lint dp[1 << 18][18];

struct cht {
	vector<pi> ch;
	bool bad(pi a, pi b, pi c) { return (__int128)(b[0] - a[0]) * (b[1] - c[1]) <= (__int128)(c[0] - b[0]) * (a[1] - b[1]); }
	void init(vector<pi> &a) {
		for (auto &x : a) {
			if (sz(ch) && ch.back()[0] == x[0])
				continue;
			while (sz(ch) >= 2 && bad(ch[sz(ch) - 2], ch.back(), x))
				ch.pop_back();
			ch.push_back(x);
		}
	}
	lint query(lint x) {
		int s = 0, e = sz(ch) - 1;
		while (s != e) {
			int m = (s + e) / 2;
			if (ch[m][0] * x + ch[m][1] > ch[m + 1][0] * x + ch[m + 1][1])
				e = m;
			else
				s = m + 1;
		}
		return ch[s][0] * x + ch[s][1];
	}
} ch[18];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	vector<lint> sum(1 << n);
	vector<vector<lint>> adj(n, vector<lint>(n, 2e9));
	for (auto &x : a)
		cin >> x;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		adj[u][v] = w;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i < n; i++) {
		dp[1 << i][i] = 0;
	}
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1)
				sum[i] += a[j];
		}
	}
	for (int i = 1; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if ((i >> j) % 2 == 1) {
				for (int k = 0; k < n; k++) {
					if (adj[j][k] < 1.1e9 && (i >> k) % 2 == 0) {
						dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + 1ll * adj[j][k] * sum[i]);
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		vector<pi> v;
		for (int j = 0; j < (1 << n); j++) {
			if ((j >> i) & 1) {
				v.push_back({sum[j], -dp[j][i]});
			}
		}
		sort(all(v), [&](const pi &a, const pi &b) {
			if (a[0] != b[0])
				return a[0] < b[0];
			return a[1] > b[1];
		});
		ch[i].init(v);
	}
	int q;
	cin >> q;
	while (q--) {
		int t, v;
		cin >> t >> v;
		v--;
		cout << ch[v].query(t) << "\n";
	}
}