#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 1005;

lint dp[MAXN][MAXN][2], sum[MAXN];
lint compL[MAXN][MAXN], compR[MAXN][MAXN];
lint opts[MAXN][2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<pi> a;
	int m;
	{
		int n, z;
		cin >> n >> z;
		vector<int> b(n);
		for (auto &x : b) {
			cin >> x;
		}
		sort(all(b));
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && b[i] == b[j])
				j++;
			a.push_back({b[i], j - i});
			i = j;
		}
		m = n;
	}
	int n = sz(a);
	int q;
	cin >> q;
	if (n > 1000) { // :thumbsdown:
		while (q--)
			cout << "No\n";
		return 0;
	}
	for (int i = 0; i < n; i++)
		sum[i + 1] = sum[i] + a[i][1];
	memset(opts, 0x3f, sizeof(opts));
	for (int i = 0; i < 2; i++) {
		memset(dp, 0x3f, sizeof(dp));
		dp[0][n - 1][i] = 0;
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j + i < n; j++) {
				int s = j, e = j + i;
				lint tot = m + 1 - (sum[e + 1] - sum[s]);
				if (s > 0) {
					lint costs = (a[e][0] - a[s - 1][0]) * tot;
					dp[s][e][1] = costs + compL[s - 1][e];
				}
				if (e + 1 < n) {
					lint costs = (a[e + 1][0] - a[s][0]) * tot;
					dp[s][e][0] = costs + compR[s][e + 1];
				}
				compL[s][e] = dp[s][e][0];
				compR[s][e] = dp[s][e][1];
				if (s > 0)
					compL[s][e] = min(compL[s][e], compL[s - 1][e] + (tot) * (a[s][0] - a[s - 1][0]));
				if (e + 1 < n) {
					compR[s][e] = min(compR[s][e], compR[s][e + 1] + tot * (a[e + 1][0] - a[e][0]));
				}
			}
		}
		for (int j = 0; j < n; j++) {
			opts[j][i] = min(dp[j][j][0], dp[j][j][1]);
		}
	}
	while (q--) {
		int s, e, x;
		cin >> s >> e >> x;
		lint ans = 1e18;
		int q = lower_bound(all(a), pi{e, -1}) - a.begin();
		for (int i = max(q - 3, 0); i < min(q + 3, n); i++) {
			ans = min(ans, 1ll * abs(a[i][0] - e) * (m + 1) + m + opts[i][0] + abs(s - a[0][0]));
			ans = min(ans, 1ll * abs(a[i][0] - e) * (m + 1) + m + opts[i][1] + abs(s - a[n - 1][0]));
		}
		//	cout << ans << endl;
		cout << (ans <= x ? "Yes" : "No") << "\n";
	}
}