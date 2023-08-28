#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 4005;

int n;
lint sum[MAXN], sumsq[MAXN];
double cost[8080808], dp[105][MAXN];

double fcost(int l, int r) {
	lint S = sum[r + 1] - sum[l];
	lint SSQ = sumsq[r + 1] - sumsq[l];
	return SSQ - 1.0 * S * S / (r - l + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k, p;
	cin >> n >> k >> p;
	k = min(k, n);
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
	}
	if (p == 1) {
		vector<vector<int>> dp(k + 1, vector<int>(n + 1, 1e9));
		dp[0][0] = 0;
		for (int i = 1; i <= k; i++) {
			vector<int> seg(1001, 1e9);
			for (int j = 0; j < n; j++) {
				for (int x = 0; x <= 1000; x++) {
					seg[x] = min(seg[x], dp[i - 1][j]);
				}
				for (int x = 0; x <= 1000; x++) {
					seg[x] += abs(a[j] - x);
				}
				dp[i][j + 1] = *min_element(all(seg));
			}
		}
		cout << dp[k][n] << "\n";
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i - 1];
		sumsq[i] = sumsq[i - 1] + a[i - 1] * a[i - 1];
	}
	int z = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			cost[z++] = fcost(i, j - 1);
		}
	}
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = 1e18;
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= k; i++) {
		int z = 0;
		for (int j = 0; j < n; j++) {
			for (int k = j; k < n; k++) {
				dp[i][k + 1] = min(dp[i][k + 1], dp[i - 1][j] + cost[z++]);
			}
		}
	}
	cout << setprecision(69) << dp[k][n] << "\n";
}