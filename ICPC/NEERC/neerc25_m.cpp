#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 1000005;

int dp[MAXN][2][2];

void solve() {
	string a, b;
	cin >> a >> b;
	int n = sz(a);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++)
				dp[i][j][k] = 1e9;
		}
	}
	dp[0][0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				for (int xi = 0; xi < 2; xi++) {
					dp[i + 1][xi][(k ^ xi)] =
						min(dp[i + 1][xi][k ^ xi], dp[i][j][k] + (xi != (a[i] - '0')) + ((k ^ xi) != (b[i] - '0')));
				}
			}
		}
	}
	int ans = 1e9;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			ans = min(ans, dp[n][i][j]);
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}