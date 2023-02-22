#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 1005;

int dp[4][MAXN][MAXN];

int solve(vector<vector<int>> a) {
	int n = sz(a);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[0][i][j] = -1e9;
			if (i)
				dp[0][i][j] = max(dp[0][i][j], dp[0][i - 1][j]);
			if (j)
				dp[0][i][j] = max(dp[0][i][j], dp[0][i][j - 1]);
			if (i == 0 && j == 0)
				dp[0][i][j] = 0;
			dp[0][i][j] += a[i][j];
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			dp[1][i][j] = -1e9;
			if (i + 1 < n)
				dp[1][i][j] = max(dp[1][i][j], dp[1][i + 1][j]);
			if (j)
				dp[1][i][j] = max(dp[1][i][j], dp[1][i][j - 1]);
			if (i == n - 1 && j == 0)
				dp[1][i][j] = 0;
			dp[1][i][j] += a[i][j];
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			dp[2][i][j] = -1e9;
			if (i + 1 < n)
				dp[2][i][j] = max(dp[2][i][j], dp[2][i + 1][j]);
			if (j + 1 < n)
				dp[2][i][j] = max(dp[2][i][j], dp[2][i][j + 1]);
			if (i == n - 1 && j == n - 1)
				dp[2][i][j] = 0;
			dp[2][i][j] += a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			dp[3][i][j] = -1e9;
			if (i)
				dp[3][i][j] = max(dp[3][i][j], dp[3][i - 1][j]);
			if (j + 1 < n)
				dp[3][i][j] = max(dp[3][i][j], dp[3][i][j + 1]);
			if (i == 0 && j == n - 1)
				dp[3][i][j] = 0;
			dp[3][i][j] += a[i][j];
		}
	}
	int ret = -1e9;
	for (int i = 0; i < n; i++) {
		vector<int> L(n, -1e9), R(n, -1e9);
		for (int j = 0; j < n; j++) {
			if (i > 0) {
				L[j] = max(L[j], dp[0][i - 1][j] + dp[1][i][j]);
				R[j] = max(R[j], dp[3][i - 1][j] + dp[2][i][j]);
			}
			if (i + 1 < n) {
				L[j] = max(L[j], dp[0][i][j] + dp[1][i + 1][j]);
				R[j] = max(R[j], dp[3][i][j] + dp[2][i + 1][j]);
			}
		}
		int sum = 0;
		int cur = -1e9;
		for (int j = 0; j < n; j++) {
			cur = max(cur + a[i][j], L[j]);
			if (j + 1 < n)
				ret = max(ret, cur + R[j + 1]);
		}
	}
	for (int i = 0; i + 2 < n; i++) {
		for (int j = 0; j + 2 < n; j++) {
			ret = max(ret, dp[0][i + 1][j] + dp[1][i + 2][j + 1] + dp[2][i + 1][j + 2] + dp[3][i][j + 1] + a[i + 1][j + 1]);
			ret = max(ret, dp[1][i + 1][j] + dp[2][i + 2][j + 1] + dp[3][i + 1][j + 2] + dp[0][i][j + 1] + a[i + 1][j + 1]);
		}
	}
	return ret;
}

int max_item_sum(std::vector<std::vector<int>> V) {
	int n = sz(V);
	vector<vector<int>> tr(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tr[j][i] = V[i][j];
		}
	}
	return max(solve(V), solve(tr));
}