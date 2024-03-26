#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 305;

pi a[MAXN];
lint dp[MAXN][MAXN], sum[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	lint n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int h, c;
		cin >> h >> c;
		a[i] = pi{h, c};
	}
	sort(a, a + n);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i - 1][0];
	memset(dp, 0x3f, sizeof(dp));
	dp[1][0] = 0;
	lint minv = 1e14;
	int j = 0;
	for (int i = 0; i < n;) {
		lint h = a[i][0];
		while (j < n && a[j][0] <= h) {
			minv = min(minv, a[j++][1]);
		}
		for (int ch = 1; ch <= n; ch++) {
			for (int proc = j; proc >= 0; proc--) {
				{
					int qroc = min(proc + ch, j);
					dp[ch][qroc] = min(dp[ch][qroc], dp[ch][proc] + k * min(lint(5e18) / k, h * (qroc - proc) - (sum[qroc] - sum[proc])));
				}
			}
		}
		for (int ch = 2; ch <= n; ch++) {
			for (int proc = 0; proc <= n; proc++) {
				dp[ch][proc] = min(dp[ch][proc], dp[ch - 1][proc] + minv);
			}
		}
		int jump = (j < n ? a[j][0] : int(2e9)) - a[i][0];
		jump = min(jump, (int)n);
		for (lint h = a[i][0] + 1; h < a[i][0] + jump; h++) {
			for (int ch = 1; ch <= min(n, 1 + n / max(1ll, h - a[i][0] - 1)); ch++) {
				for (int proc = j; proc >= 0; proc--) {
					{
						int qroc = min(proc + ch, j);
						dp[ch][qroc] = min(dp[ch][qroc], dp[ch][proc] + k * min(lint(5e18) / k, h * (qroc - proc) - (sum[qroc] - sum[proc])));
					}
				}
			}
		}
		i = j;
	}
	lint ans = 1e18;
	for (int i = 1; i <= n; i++)
		ans = min(ans, dp[i][n]);
	cout << ans << "\n";
}