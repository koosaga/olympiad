#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, c;
	cin >> n >> c;
	vector<lint> a(n);
	for (auto &x : a)
		cin >> x;
	sort(all(a));
	if (c >= n) {
		cout << a[n - 1] << "\n";
		return 0;
	}
	vector<vector<lint>> dp(n, vector<lint>((n / c) + 5, 1e18));
	vector<lint> sum(n + 1);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i - 1];
	for (int i = 0; i < n; i++) {
		if (i < c)
			dp[i][0] = a[i];
		for (int j = 0; j <= (n - i - 1) / c + 3; j++) {
			for (int k = 0; k <= min(c, j + 1); k++) {
				if (i < c) {
					if (k)
						dp[i][j] = min(dp[i][j], dp[k - 1][j - k + 1] + sum[k] + a[i]);
				} else if (i - c + k >= 0) {
					dp[i][j] = min(dp[i][j], dp[i - c + k][j - k + 1] + sum[k] + a[i]);
				}
			}
		}
	}
	cout << dp[n - 1][0] << "\n";
}