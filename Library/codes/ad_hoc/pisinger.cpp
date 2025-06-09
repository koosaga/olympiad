// Given n positive integers in range [1, m], find a subset that sums to T.
// Runs in time O(nm)
// Source: https://atcoder.jp/contests/abc221/submissions/60912284

vector<int> SubsetSum(const vector<int> &d, int x) {
	auto chmin = [&](int &x, int y) { x = min(x, y); };
	auto chmax = [&](int &x, int y) { x = max(x, y); };

	int n = d.size(), s = 0;
	for (int i = 0; i < n; i++)
		s += d[i];
	if (x < 0 || s < x)
		return {};
	bool flip = (x * 2 < s);
	if (flip)
		x = s - x;
	int si = 0, m = 0;
	while (x > 0 && si < n)
		x -= d[si++];
	for (int i = 0; i < n; i++)
		chmax(m, d[i]);
	int m2 = m * 2 + 1;
	vector<vector<int>> dp(n + 1);
	const int INF = 1001001001;
	for (int i = si; i <= n; i++)
		dp[i] = vector<int>(m2, INF);
	dp[si][m - x] = 0;
	vector<int> res;
	for (int i = si; i <= n; i++) {
		for (int k = m2 - 1; k >= 0; k--) {
			if (k > m) {
				int r = si;
				if (i > si)
					chmin(r, dp[i - 1][k]);
				for (int j = dp[i][k]; j < r; j++) {
					chmin(dp[i][k - d[j]], j + 1);
				}
			}
			if (i < n) {
				chmin(dp[i + 1][k], dp[i][k]);
				if (k < m)
					chmin(dp[i + 1][k + d[i]], dp[i][k]);
			}
		}
		if (dp[i][m] != INF) {
			res = vector<int>(n);
			fill(res.begin(), res.begin() + si, 1);
			int k = m;
			while (1) {
				int j = dp[i][k];
				if (j == 0 && i == si)
					break;
				if (j != INF && j != 0 && k + d[j - 1] < m2 && dp[i][k + d[j - 1]] < j) {
					k += d[j - 1];
					res[j - 1] = 0;
					continue;
				}
				i--;
				if (dp[i][k] != j)
					k -= d[i], res[i] = 1;
			}
			break;
		}
	}
	if (flip)
		for (int i = 0; i < (int)res.size(); i++)
			res[i] ^= 1;
	return res;
}
