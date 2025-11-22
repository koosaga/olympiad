#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int B = 5;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int n = sz(s);
		vector<array<int, B>> dp(n);
		int ans = -1e9;
		for (int i = 0; i < n; i++) {
			fill(all(dp[i]), -1e9);
			if (i == 0)
				dp[0][0] = 0;
			for (int j = 0; j < B && j <= i; j++) {
				for (int k = 1; k < B && i + k <= n; k++) {
					if (j == k && s.substr(i - j, j) == s.substr(i, k))
						continue;
					dp[i][k] = max(dp[i][k], dp[i - j][j] + 1);
				}
			}
			if (n - i < B)
				ans = max(ans, dp[i][n - i]);
		}
		cout << ans << "\n";
	}
}