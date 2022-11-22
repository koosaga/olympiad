#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 505;

int dp[2][MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, p, q;
	cin >> n >> p >> q;
	vector<string> a(n), b(p), c(q);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < p; i++)
		cin >> b[i];
	for (int i = 0; i < q; i++)
		cin >> c[i];
	for (int i = 0; i <= n; i++) {
		int cur = i % 2, nxt = (i + 1) % 2;
		memset(dp[nxt], 0, sizeof(dp[nxt]));

		for (int j = 0; j <= p; j++) {
			for (int k = 0; k <= q; k++) {
				if (i + 1 <= n) {
					dp[nxt][j][k] = max(dp[nxt][j][k], dp[cur][j][k]);
					if (j + 1 <= p && b[j] == a[i])
						dp[nxt][j + 1][k] = max(1 + dp[cur][j][k], dp[nxt][j + 1][k]);
					if (k + 1 <= q && c[k] == a[i])
						dp[nxt][j][k + 1] = max(1 + dp[cur][j][k], dp[nxt][j][k + 1]);
				}
				if (j + 1 <= p)
					dp[cur][j + 1][k] = max(dp[cur][j][k], dp[cur][j + 1][k]);
				if (k + 1 <= q)
					dp[cur][j][k + 1] = max(dp[cur][j][k], dp[cur][j][k + 1]);
			}
		}
	}

	cout << dp[n % 2][p][q] << "\n";
}